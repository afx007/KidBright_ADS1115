Blockly.Blocks['i2c_ads1115.getValue'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(Blockly.Msg.I2C_TITLE)
		
        .appendField(Blockly.Msg.I2C_CHANNEL_TITLE)
        .appendField(new Blockly.FieldDropdown([["CH_0","0"], ["CH_1","1"]]), "I2C_CHANNEL")

        .appendField(Blockly.Msg.I2C_ADDRESS_TITLE)
        .appendField(new Blockly.FieldDropdown([["0x48","72"], ["0x49","73"], ["0x4A","74"], ["0X4B","75"]]), "I2C_ADDRESS")

        .appendField(Blockly.Msg.I2C_INPUT_TITLE)
        .appendField(new Blockly.FieldDropdown([["A0","0"], ["A1","1"], ["A2","2"], ["A3","3"]]), "I2C_INPUT");

    this.setInputsInline(true);
    this.setOutput(true, "Number");
    this.setColour(290);
 this.setTooltip(Blockly.Msg.I2C_TOOLTIP);
 this.setHelpUrl(Blockly.Msg.I2C_HELP_URL);
  }
};
