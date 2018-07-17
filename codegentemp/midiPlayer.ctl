-- ======================================================================
-- midiPlayer.ctl generated from midiPlayer
-- 07/11/2018 at 22:33
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-041 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(0,4)";
attribute port_location of \UART:tx(0)\ : label is "PORT(0,5)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(3,0)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(3,1)";

-- === RGB LED ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(3,4)"; -- RED LED
attribute port_location of LED_Green(0) : label is "PORT(2,6)"; -- GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(3,6)"; -- BLUE LED

-- === USER SWITCH ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(0,7)";
 
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
