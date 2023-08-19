module Cronometro (
		input  logic [3:0] buttons,    //    button_pio_external_connection.export
		input  logic       clk,                                  //                               clk.clk
		output logic [7:0] leds,       //       led_pio_external_connection.export
		input  logic       rst_n,                            //                             reset.reset_n
		output logic [6:0] seven_seg // seven_seg_pio_external_connection.export
);
	test_count test(
		.button_pio_external_connection_export(buttons),    //    button_pio_external_connection.export
		.clk_clk(clk),                                  //                               clk.clk
		.led_pio_external_connection_export(leds),       //       led_pio_external_connection.export
		.reset_reset_n(rst_n),                            //                             reset.reset_n
		.seven_seg_pio_external_connection_export(seven_seg)
	);
	
endmodule