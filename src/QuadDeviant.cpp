#include "plugin.hpp"


struct QuadDeviant : Module {
	enum ParamId {
		TOP4_PARAM,
		TOP3_PARAM,
		TOP2_PARAM,
		TOP1_PARAM,
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
		LED1_LIGHT,
		LED2_LIGHT,
		LED3_LIGHT,
		LED4_LIGHT,
		SUMLED_LIGHT,
		INVLED_LIGHT,
		MAXLED_LIGHT,
		MINLED_LIGHT,
		POSLED_LIGHT,
		NEGLED_LIGHT,
		FULLLED_LIGHT,
		INVFULLLED_LIGHT,
		AVGLED_LIGHT,
		SLEWLED_LIGHT,
		LIGHTS_LEN
	};

	QuadDeviant() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(TOP4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(TOP3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(TOP2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(TOP1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BOTTOM1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BOTTOM2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BOTTOM3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BOTTOM4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(RANGE1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(RANGE2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(RANGE3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(RANGE4_PARAM, 0.f, 1.f, 0.f, "");
		configInput(CLK1_INPUT, "");
		configInput(CLK2_INPUT, "");
		configInput(CLK3_INPUT, "");
		configInput(CLK4_INPUT, "");
		configInput(TOPCV1_INPUT, "");
		configInput(TOPCV2_INPUT, "");
		configInput(TOPCV3_INPUT, "");
		configInput(TOPCV4_INPUT, "");
		configInput(BOTTOMCV1_INPUT, "");
		configInput(BOTTOMCV2_INPUT, "");
		configInput(BOTTOMCV3_INPUT, "");
		configInput(BOTTOMCV4_INPUT, "");
		configOutput(SUMOUT_OUTPUT, "");
		configOutput(INVSUMOUT_OUTPUT, "");
		configOutput(MAXOUT_OUTPUT, "");
		configOutput(MINOUT_OUTPUT, "");
		configOutput(POSOUT_OUTPUT, "");
		configOutput(NEGOUT_OUTPUT, "");
		configOutput(FULLOUT_OUTPUT, "");
		configOutput(INVFULLOUT_OUTPUT, "");
		configOutput(OUT1_OUTPUT, "");
		configOutput(OUT2_OUTPUT, "");
		configOutput(OUT3_OUTPUT, "");
		configOutput(OUT4_OUTPUT, "");
		configOutput(AVGOUT_OUTPUT, "");
		configOutput(SLEWOUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct QuadDeviantWidget : ModuleWidget {
	QuadDeviantWidget(QuadDeviant* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/panels/QuadDeviant.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.019, 25.23)), module, QuadDeviant::TOP4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.685, 25.23)), module, QuadDeviant::TOP3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(55.352, 25.23)), module, QuadDeviant::TOP2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(78.019, 25.23)), module, QuadDeviant::TOP1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.019, 45.608)), module, QuadDeviant::BOTTOM1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.685, 45.608)), module, QuadDeviant::BOTTOM2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(55.352, 45.608)), module, QuadDeviant::BOTTOM3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(78.019, 45.608)), module, QuadDeviant::BOTTOM4_PARAM));

		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(10.019, 61.826)), module, QuadDeviant::RANGE1_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(32.685, 61.826)), module, QuadDeviant::RANGE2_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(55.352, 61.826)), module, QuadDeviant::RANGE3_PARAM));
		addParam(createParamCentered<CKSSThreeHorizontal>(mm2px(Vec(78.019, 61.826)), module, QuadDeviant::RANGE4_PARAM));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(10.019, 76.014)), module, QuadDeviant::CLK1_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.685, 75.929)), module, QuadDeviant::CLK2_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(55.352, 75.929)), module, QuadDeviant::CLK3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(78.019, 75.929)), module, QuadDeviant::CLK4_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(10.019, 88.876)), module, QuadDeviant::TOPCV1_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.685, 88.876)), module, QuadDeviant::TOPCV2_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(55.352, 88.876)), module, QuadDeviant::TOPCV3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(78.019, 88.876)), module, QuadDeviant::TOPCV4_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(10.019, 101.449)), module, QuadDeviant::BOTTOMCV1_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.685, 101.449)), module, QuadDeviant::BOTTOMCV2_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(55.352, 101.449)), module, QuadDeviant::BOTTOMCV3_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(78.019, 101.449)), module, QuadDeviant::BOTTOMCV4_INPUT));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(92.449, 22.129)), module, QuadDeviant::SUMOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(104.171, 22.135)), module, QuadDeviant::INVSUMOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(92.449, 45.026)), module, QuadDeviant::MAXOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(104.171, 44.973)), module, QuadDeviant::MINOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(92.449, 67.847)), module, QuadDeviant::POSOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(104.171, 67.811)), module, QuadDeviant::NEGOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(92.449, 90.743)), module, QuadDeviant::FULLOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(104.171, 90.726)), module, QuadDeviant::INVFULLOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(10.019, 113.602)), module, QuadDeviant::OUT1_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(32.685, 113.602)), module, QuadDeviant::OUT2_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(55.352, 113.602)), module, QuadDeviant::OUT3_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(78.019, 113.602)), module, QuadDeviant::OUT4_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(92.449, 113.602)), module, QuadDeviant::AVGOUT_OUTPUT));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(104.171, 113.602)), module, QuadDeviant::SLEWOUT_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(10.019, 14.029)), module, QuadDeviant::LED1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(32.685, 14.029)), module, QuadDeviant::LED2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(55.352, 14.029)), module, QuadDeviant::LED3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(78.019, 14.029)), module, QuadDeviant::LED4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.449, 14.029)), module, QuadDeviant::SUMLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(104.171, 14.029)), module, QuadDeviant::INVLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.449, 36.926)), module, QuadDeviant::MAXLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(104.171, 36.867)), module, QuadDeviant::MINLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.449, 59.747)), module, QuadDeviant::POSLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(104.171, 59.705)), module, QuadDeviant::NEGLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.449, 82.643)), module, QuadDeviant::FULLLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(104.171, 82.62)), module, QuadDeviant::INVFULLLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(92.449, 105.502)), module, QuadDeviant::AVGLED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(104.171, 105.496)), module, QuadDeviant::SLEWLED_LIGHT));
	}
};


Model* modelQuadDeviant = createModel<QuadDeviant, QuadDeviantWidget>("QuadDeviant");