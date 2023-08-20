module tallernios
(
	input logic clk,
					rst_n,
	input logic switch,
	output logic[6:0] leds
);

	logic[3:0] number;
	

	platform plat
	(
		.clk_clk(clk),
		.pio_leds_0_external_connection_export(number),
		.pio_switch_0_external_connection_export(switch),
		.reset_reset_n(rst_n)
	);
	
	seven_segment_display(.number(number), .segment(leds));

endmodule