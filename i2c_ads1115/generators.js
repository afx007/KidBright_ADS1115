Blockly.JavaScript['i2c_ads1115.getValue'] = function(block) {

  var i2c_ch = block.getFieldValue('I2C_CHANNEL');
  var i2c_ad = block.getFieldValue('I2C_ADDRESS');
  var i2c_io = block.getFieldValue('I2C_INPUT');
  // TODO: Assemble JavaScript into code variable.

	  var code = 'DEV_I2C1.I2C_ADS1115('+i2c_ch+','+i2c_ad+').getValue('+i2c_io+')';


  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};
