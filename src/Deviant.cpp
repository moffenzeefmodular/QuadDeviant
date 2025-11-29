#include "plugin.hpp"

struct Deviant : Module {
    enum ParamId {
        TOP_1__PARAM,
        TOP_2_PARAM,
        BOTTOM_1_PARAM,
        BOTTOM_2_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        BANG_1_INPUT,
        CH__1_TOP_INPUT,
        CH__1_BOTTOM_INPUT,
        BANG_2_INPUT,
        CH__2_TOP_INPUT,
        CH__2_BOTTOM_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        CH__1_OUTPUT,
        CH__2_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LED_NEG_1_LIGHT,
        LED_POS_1_LIGHT,
        LED_NEG_2_LIGHT,
        LED_POS_2_LIGHT,
        LIGHTS_LEN
    };

    Deviant() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

        // All params now 0-1
        configParam(TOP_1__PARAM, 0.f, 1.f, 1.f, "Top 1", "");     
        configParam(TOP_2_PARAM, 0.f, 1.f, 1.f, "Top 2", "");     
        configParam(BOTTOM_1_PARAM, 0.f, 1.f, 0.f, "Bottom 1", "");  
        configParam(BOTTOM_2_PARAM, 0.f, 1.f, 0.f, "Bottom 2", "");  

        configInput(BANG_1_INPUT, "Bang! 1 Gate");
        configInput(CH__1_TOP_INPUT, "Top 1 CV");
        configInput(CH__1_BOTTOM_INPUT, "Bottom 1 CV");
        configInput(BANG_2_INPUT, "Bang! 2 Gate");
        configInput(CH__2_TOP_INPUT, "Top 2 CV");
        configInput(CH__2_BOTTOM_INPUT, "Bottom 2 CV");
        configOutput(CH__1_OUTPUT, "Deviant 1 CV");
        configOutput(CH__2_OUTPUT, "Deviant 2 CV");
    }

    float lastBang1Input = 0.0f;
    float lastBang2Input = 0.0f;
    float randomVoltage1 = 0.01f; 
    float randomVoltage2 = 0.01f;

    // Rescale helper: 0-1 param -> -5V to 5V
    float paramToVoltage(float p) {
        return -5.f + p * 10.f;
    }

    void process(const ProcessArgs& args) override {
        // Rising edge detection
        bool bang1Triggered = false;
        if (inputs[BANG_1_INPUT].isConnected()) {
            float bang1Input = inputs[BANG_1_INPUT].getVoltage();
            if (bang1Input > 0.5f && lastBang1Input <= 0.5f) bang1Triggered = true;
            lastBang1Input = bang1Input;
        }

        bool bang2Triggered = false;
        if (inputs[BANG_2_INPUT].isConnected()) {
            float bang2Input = inputs[BANG_2_INPUT].getVoltage();
            if (bang2Input > 0.5f && lastBang2Input <= 0.5f) bang2Triggered = true;
            lastBang2Input = bang2Input;
        }

        // Jack normalizing
        if (!inputs[BANG_2_INPUT].isConnected()) bang2Triggered = bang1Triggered;

        // Bang 1
        if (bang1Triggered) {
            float topValue = paramToVoltage(params[TOP_1__PARAM].getValue()) + inputs[CH__1_TOP_INPUT].getVoltage();
            float bottomValue = paramToVoltage(params[BOTTOM_1_PARAM].getValue()) + inputs[CH__1_BOTTOM_INPUT].getVoltage();
            if (bottomValue >= topValue) bottomValue = topValue;
            randomVoltage1 = clamp(bottomValue + (topValue - bottomValue) * random::uniform(), -5.f, 5.f);
        }

        // Bang 2
        if (bang2Triggered) {
            float topValue = paramToVoltage(params[TOP_2_PARAM].getValue()) + inputs[CH__2_TOP_INPUT].getVoltage();
            float bottomValue = paramToVoltage(params[BOTTOM_2_PARAM].getValue()) + inputs[CH__2_BOTTOM_INPUT].getVoltage();
            if (bottomValue >= topValue) bottomValue = topValue;
            randomVoltage2 = clamp(bottomValue + (topValue - bottomValue) * random::uniform(), -5.f, 5.f);
        }

        // Directly output random voltages
        outputs[CH__1_OUTPUT].setVoltage(randomVoltage1);
        outputs[CH__2_OUTPUT].setVoltage(randomVoltage2);

        // LEDs
        lights[LED_POS_1_LIGHT].setBrightness(clamp(randomVoltage1, 0.f, 5.f) / 5.f);
        lights[LED_NEG_1_LIGHT].setBrightness(clamp(-randomVoltage1, 0.f, 5.f) / 5.f);
        lights[LED_POS_2_LIGHT].setBrightness(clamp(randomVoltage2, 0.f, 5.f) / 5.f);
        lights[LED_NEG_2_LIGHT].setBrightness(clamp(-randomVoltage2, 0.f, 5.f) / 5.f);
    }
};

struct DeviantWidget : ModuleWidget {
    DeviantWidget(Deviant* module) {
        setModule(module);
        setPanel(createPanel(
            asset::plugin(pluginInstance, "res/panels/Deviant.svg"),
            asset::plugin(pluginInstance, "res/panels/Deviant-dark.svg")
        ));

        addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(11.061, 24.335)), module, Deviant::TOP_1__PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(39.798, 24.372)), module, Deviant::TOP_2_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(11.047, 46.773)), module, Deviant::BOTTOM_1_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(39.74, 46.767)), module, Deviant::BOTTOM_2_PARAM));

        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.813, 97.162)), module, Deviant::BANG_1_INPUT));
        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.771, 97.058)), module, Deviant::CH__1_TOP_INPUT));
        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(30.906, 97.007)), module, Deviant::CH__1_BOTTOM_INPUT));
        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.835, 112.448)), module, Deviant::BANG_2_INPUT));
        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.727, 112.435)), module, Deviant::CH__2_TOP_INPUT));
        addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(30.927, 112.369)), module, Deviant::CH__2_BOTTOM_INPUT));

        addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(41.812, 97.073)), module, Deviant::CH__1_OUTPUT));
        addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(41.899, 112.441)), module, Deviant::CH__2_OUTPUT));

        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.57, 13.957)), module, Deviant::LED_NEG_1_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(13.575, 13.957)), module, Deviant::LED_POS_1_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(37.226, 13.957)), module, Deviant::LED_NEG_2_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(42.238, 13.995)), module, Deviant::LED_POS_2_LIGHT));
    }
};

Model* modelDeviant = createModel<Deviant, DeviantWidget>("Deviant");
