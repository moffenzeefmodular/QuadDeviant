#include "plugin.hpp"

struct QuadDeviant : Module {
enum ParamId {
    BUS1_PARAM,
    BUS2_PARAM,
    BUS3_PARAM,
    BUS4_PARAM,
    TOP1_PARAM,
    TOP2_PARAM,
    TOP3_PARAM,
    TOP4_PARAM,
    BOTTOM1_PARAM,
    BOTTOM2_PARAM,
    BOTTOM3_PARAM,
    BOTTOM4_PARAM,
    RANGE1_PARAM,
    RANGE2_PARAM,
    RANGE3_PARAM,
    RANGE4_PARAM,
    PARAMS_LEN
};
	enum InputId {
		CLK1_INPUT,
		CLK2_INPUT,
		CLK3_INPUT,
		CLK4_INPUT,
		TOPCV1_INPUT,
		TOPCV2_INPUT,
		TOPCV3_INPUT,
		TOPCV4_INPUT,
		BOTTOMCV1_INPUT,
		BOTTOMCV2_INPUT,
		BOTTOMCV3_INPUT,
		BOTTOMCV4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SUMOUT_OUTPUT,
		INVSUMOUT_OUTPUT,
		MAXOUT_OUTPUT,
		MINOUT_OUTPUT,
		POSOUT_OUTPUT,
		NEGOUT_OUTPUT,
		FULLOUT_OUTPUT,
		INVFULLOUT_OUTPUT,
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		AVGOUT_OUTPUT,
		SLEWOUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LED1RED_LIGHT,
		LED2RED_LIGHT,
		LED3RED_LIGHT,
		LED4RED_LIGHT,
		SUMLEDRED_LIGHT,
		INVLEDRED_LIGHT,
		MAXLEDRED_LIGHT,
		MINLEDRED_LIGHT,
		POSLEDRED_LIGHT,
		NEGLEDRED_LIGHT,
		FULLLEDRED_LIGHT,
		INVFULLLEDRED_LIGHT,
		AVGLEDRED_LIGHT,
		SLEWLEDRED_LIGHT,
		LED1GREEN_LIGHT,
		LED2GREEN_LIGHT,
		LED3GREEN_LIGHT,
		LED4GREEN_LIGHT,
		SUMLEDGREEN_LIGHT,
		INVLEDGREEN_LIGHT,
		MAXLEDGREEN_LIGHT,
		MINLEDGREEN_LIGHT,
		POSLEDGREEN_LIGHT,
		NEGLEDGREEN_LIGHT,
		FULLLEDGREEN_LIGHT,
		INVFULLLEDGREEN_LIGHT,
		AVGLEDGREEN_LIGHT,
		SLEWLEDGREEN_LIGHT,
		BUS1LED_LIGHT,
		BUS2LED_LIGHT,
		BUS3LED_LIGHT,
		BUS4LED_LIGHT,
		LIGHTS_LEN
	};

	QuadDeviant() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configSwitch(BUS1_PARAM, 0.f, 1.f, 0.f, "Bus 1");
		configSwitch(BUS2_PARAM, 0.f, 1.f, 0.f, "Bus 2");
		configParam(TOP4_PARAM, 0.f, 1.f, 1.f, "Top 4", "%", 0.f, 100.f);
		configParam(TOP3_PARAM, 0.f, 1.f, 1.f, "Top 3", "%", 0.f, 100.f);
		configParam(TOP2_PARAM, 0.f, 1.f, 1.f, "Top 2", "%", 0.f, 100.f);
		configParam(TOP1_PARAM, 0.f, 1.f, 1.f, "Top 1", "%", 0.f, 100.f);
		configSwitch(BUS3_PARAM, 0.f, 1.f, 0.f, "Bus 3");
		configSwitch(BUS4_PARAM, 0.f, 1.f, 0.f, "Bus 4");
		configParam(BOTTOM1_PARAM, 0.f, 1.f, 0.f, "Bottom 1", "%", 0.f, 100.f);
		configParam(BOTTOM2_PARAM, 0.f, 1.f, 0.f, "Bottom 2", "%", 0.f, 100.f);
		configParam(BOTTOM3_PARAM, 0.f, 1.f, 0.f, "Bottom 3", "%", 0.f, 100.f);
		configParam(BOTTOM4_PARAM, 0.f, 1.f, 0.f, "Bottom 4", "%", 0.f, 100.f);
		configSwitch(RANGE1_PARAM, 0.f, 2.f, 0.f, "Range 1", {"5vpp", "10vpp", "20vpp"});
		configSwitch(RANGE2_PARAM, 0.f, 2.f, 0.f, "Range 2",  {"5vpp", "10vpp", "20vpp"});
		configSwitch(RANGE3_PARAM, 0.f, 2.f, 0.f, "Range 3", {"5vpp", "10vpp", "20vpp"});
		configSwitch(RANGE4_PARAM, 0.f, 2.f, 0.f, "Range 4", {"5vpp", "10vpp", "20vpp"});
		configInput(CLK1_INPUT, "Clock 1");
		configInput(CLK2_INPUT, "Clock 2");
		configInput(CLK3_INPUT, "Clock 3");
		configInput(CLK4_INPUT, "Clock 4");
		configInput(TOPCV1_INPUT, "Top CV 1");
		configInput(TOPCV2_INPUT, "Top CV 2");
		configInput(TOPCV3_INPUT, "Top CV 3");
		configInput(TOPCV4_INPUT, "Top CV 4");
		configInput(BOTTOMCV1_INPUT, "Bottom CV 1");
		configInput(BOTTOMCV2_INPUT, "Bottom CV 2");
		configInput(BOTTOMCV3_INPUT, "Bottom CV 3");
		configInput(BOTTOMCV4_INPUT, "Bottom CV 4");
		configOutput(SUMOUT_OUTPUT, "Sum");
		configOutput(INVSUMOUT_OUTPUT, "Inverse Sum");
		configOutput(MAXOUT_OUTPUT, "Max");
		configOutput(MINOUT_OUTPUT, "Min");
		configOutput(POSOUT_OUTPUT, "Positive");
		configOutput(NEGOUT_OUTPUT, "Negative");
		configOutput(FULLOUT_OUTPUT, "Full Wave Rectified");
		configOutput(INVFULLOUT_OUTPUT, "Inverse Full Wave Rectified");
		configOutput(OUT1_OUTPUT, "Ch. 1");
		configOutput(OUT2_OUTPUT, "Ch. 2");
		configOutput(OUT3_OUTPUT, "Ch. 3");
		configOutput(OUT4_OUTPUT, "Ch. 4");
		configOutput(AVGOUT_OUTPUT, "Average");
		configOutput(SLEWOUT_OUTPUT, "Slew");
	}


// Bus Buttons
dsp::SchmittTrigger busTrigger[4];
bool busState[4] = {true, true, true, };

void onReset() override {
    // Set all bus buttons to true
    for (int i = 0; i < 4; i++) {
        busState[i] = true;
    }
}

void onRandomize() override {
    for (int i = 0; i < 4; i++) {
        busState[i] = (rand() % 2 == 0);
    }
}


void process(const ProcessArgs &args) override {

	//Bus buttons
    for (int i = 0; i < 4; i++) {
        int paramId = BUS1_PARAM + i;
        int lightId = BUS1LED_LIGHT + i;

        if (busTrigger[i].process(params[paramId].getValue())) {
            busState[i] = !busState[i];
        }

        lights[lightId].setBrightnessSmooth(busState[i] ? 1.f : 0.f, args.sampleTime);
    }
}

};


struct QuadDeviantWidget : ModuleWidget {

	    // Store pointers to ParamQuantities for dynamic labels
    ParamQuantity* bus1Q = nullptr;
    ParamQuantity* bus2Q = nullptr;
    ParamQuantity* bus3Q = nullptr;
    ParamQuantity* bus4Q = nullptr;

	QuadDeviantWidget(QuadDeviant* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/panels/QuadDeviant.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(mm2px(Vec(108.324, 18.277)), module, QuadDeviant::BUS1_PARAM, QuadDeviant::BUS1LED_LIGHT));
		addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(mm2px(Vec(121.633, 18.308)), module, QuadDeviant::BUS2_PARAM, QuadDeviant::BUS2LED_LIGHT));
		addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(mm2px(Vec(108.324, 30.54)), module, QuadDeviant::BUS3_PARAM, QuadDeviant::BUS3LED_LIGHT));
		addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(mm2px(Vec(121.633, 30.531)), module, QuadDeviant::BUS4_PARAM, QuadDeviant::BUS4LED_LIGHT));

		//addParam(createParamCentered<LEDBezel>(mm2px(Vec(121.633, 18.308)), module, QuadDeviant::BUS2_PARAM));
		//addParam(createParamCentered<LEDBezel>(mm2px(Vec(108.324, 30.54)), module, QuadDeviant::BUS3_PARAM));
		//addParam(createParamCentered<LEDBezel>(mm2px(Vec(121.633, 30.531)), module, QuadDeviant::BUS4_PARAM));
    
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(14.664, 25.23)), module, QuadDeviant::TOP1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(39.664, 25.23)), module, QuadDeviant::TOP2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64.664, 25.23)), module, QuadDeviant::TOP3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(89.664, 25.23)), module, QuadDeviant::TOP4_PARAM));
	
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(14.664, 45.608)), module, QuadDeviant::BOTTOM1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(39.664, 45.608)), module, QuadDeviant::BOTTOM2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64.664, 45.608)), module, QuadDeviant::BOTTOM3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(89.664, 45.608)), module, QuadDeviant::BOTTOM4_PARAM));

		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(14.664, 61.826)), module, QuadDeviant::RANGE1_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(39.664, 61.826)), module, QuadDeviant::RANGE2_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(64.664, 61.826)), module, QuadDeviant::RANGE3_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(89.664, 61.826)), module, QuadDeviant::RANGE4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(14.664, 76.014)), module, QuadDeviant::CLK1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(39.664, 75.929)), module, QuadDeviant::CLK2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(64.664, 75.929)), module, QuadDeviant::CLK3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.664, 75.929)), module, QuadDeviant::CLK4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(14.664, 88.876)), module, QuadDeviant::TOPCV1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(39.664, 88.876)), module, QuadDeviant::TOPCV2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(64.664, 88.876)), module, QuadDeviant::TOPCV3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.664, 88.876)), module, QuadDeviant::TOPCV4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(14.664, 101.449)), module, QuadDeviant::BOTTOMCV1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(39.664, 101.449)), module, QuadDeviant::BOTTOMCV2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(64.664, 101.449)), module, QuadDeviant::BOTTOMCV3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.664, 101.449)), module, QuadDeviant::BOTTOMCV4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(108.324, 44.897)), module, QuadDeviant::SUMOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(121.633, 44.9)), module, QuadDeviant::INVSUMOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(108.324, 62.102)), module, QuadDeviant::MAXOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(121.633, 62.047)), module, QuadDeviant::MINOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(108.324, 79.23)), module, QuadDeviant::POSOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(121.633, 79.194)), module, QuadDeviant::NEGOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(108.324, 96.435)), module, QuadDeviant::FULLOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(121.633, 96.417)), module, QuadDeviant::INVFULLOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.664, 113.602)), module, QuadDeviant::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.664, 113.602)), module, QuadDeviant::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(64.664, 113.602)), module, QuadDeviant::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(89.664, 113.602)), module, QuadDeviant::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(108.324, 113.602)), module, QuadDeviant::AVGOUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(121.633, 113.602)), module, QuadDeviant::SLEWOUT_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(14.664, 14.029)), module, QuadDeviant::LED1RED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(14.664, 14.029)), module, QuadDeviant::LED1GREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(39.664, 14.029)), module, QuadDeviant::LED2RED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(39.664, 14.029)), module, QuadDeviant::LED2GREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(64.664, 14.029)), module, QuadDeviant::LED3RED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(64.664, 14.029)), module, QuadDeviant::LED3GREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(89.664, 14.029)), module, QuadDeviant::LED4RED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(89.664, 14.029)), module, QuadDeviant::LED4GREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(108.324, 38.165)), module, QuadDeviant::SUMLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(108.324, 38.165)), module, QuadDeviant::SUMLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.633, 38.162)), module, QuadDeviant::INVLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(121.633, 38.162)), module, QuadDeviant::INVLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(108.324, 54.841)), module, QuadDeviant::MAXLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(108.324, 54.841)), module, QuadDeviant::MAXLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.633, 54.78)), module, QuadDeviant::MINLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(121.633, 54.78)), module, QuadDeviant::MINLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(108.324, 71.969)), module, QuadDeviant::POSLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(108.324, 71.969)), module, QuadDeviant::POSLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.633, 71.927)), module, QuadDeviant::NEGLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(121.633, 71.927)), module, QuadDeviant::NEGLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(108.324, 89.174)), module, QuadDeviant::FULLLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(108.324, 89.174)), module, QuadDeviant::FULLLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.633, 89.15)), module, QuadDeviant::INVFULLLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(121.633, 89.15)), module, QuadDeviant::INVFULLLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(108.324, 106.341)), module, QuadDeviant::AVGLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(108.324, 106.341)), module, QuadDeviant::AVGLEDGREEN_LIGHT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(121.633, 106.335)), module, QuadDeviant::SLEWLEDRED_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(121.633, 106.335)), module, QuadDeviant::SLEWLEDGREEN_LIGHT));

  if (module) {
            bus1Q = module->paramQuantities[QuadDeviant::BUS1_PARAM];
            bus2Q = module->paramQuantities[QuadDeviant::BUS2_PARAM];
            bus3Q = module->paramQuantities[QuadDeviant::BUS3_PARAM];
            bus4Q = module->paramQuantities[QuadDeviant::BUS4_PARAM];
        }
    }

   void step() override {
        ModuleWidget::step();

        if (!module) return;
        auto* m = dynamic_cast<QuadDeviant*>(module);

        ParamQuantity* qs[4] = {bus1Q, bus2Q, bus3Q, bus4Q};

        // 🔥 Loop through channels for dynamic labeling
        for (int i = 0; i < 4; i++) {
            if (qs[i]) {
                qs[i]->name = m->busState[i]
                    ? ("Ch. " + std::to_string(i + 1) + " (ON)")
                    : ("Ch. " + std::to_string(i + 1) + " (OFF)");
            }
        }
    }
};


Model* modelQuadDeviant = createModel<QuadDeviant, QuadDeviantWidget>("QuadDeviant");