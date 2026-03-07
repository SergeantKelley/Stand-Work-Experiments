RTS_PACKAGE_HEADER_BEGIN(AISOSO)

  RTS_TESTCOMP_BEGIN(AISOSO)

    /* для управления плагином sample */


    RTS_PROPERTY(plugin_PARAM_OUT, "описание", "--")
    RTS_PROPERTY(plugin_PARAM_OUT, "событийность", false)
    RTS_OUTPUT_PARAM(plugin_PARAM_OUT, uint32)

    RTS_PROPERTY(plugin_PARAM_IN, "описание", "--")
    RTS_PROPERTY(plugin_PARAM_IN, "событийность", true)
    RTS_INPUT_PARAM(plugin_PARAM_IN, uint32)

  RTS_TESTCOMP_END()
RTS_PACKAGE_HEADER_END()