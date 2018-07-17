-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-149 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(7,0)";
attribute port_location of \UART:tx(0)\ : label is "PORT(7,1)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(3,0)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(3,1)";

-- === CAPSENCE LED ===
attribute port_location of LED_Green(0) : label is "PORT(2,2)"; -- SLIDER 0 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(2,0)"; -- SLIDER 1 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(1,6)"; -- SLIDER 2 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(1,4)"; -- SLIDER 3 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(1,2)"; -- SLIDER 4 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(1,0)"; -- SLIDER 5 GREEN LED

attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(5,7)"; -- BUTTON 2 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(5,5)"; -- BUTTON 1 GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(5,2)"; -- BUTTON 0 GREEN LED

-- === USER LED ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(3,4)"; -- USER BLUE LED

-- === USER SWITCH ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(3,7)";