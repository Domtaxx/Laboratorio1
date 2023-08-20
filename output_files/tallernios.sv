module tallernios
(
	input logic clk,
					rst_n,
	input logic[1:0] switch,
	output logic[6:0] display1,
	output logic[6:0] display2
);

	logic[7:0] number;
	

	platform plat
	(
		.clk_clk(clk),
		.pio_leds_0_external_connection_export(number),
		.pio_switch_0_external_connection_export(switch),
		.reset_reset_n(rst_n)
	);
	

	two_seven_segment_displays(
    .decimal_number(number),
    .segment_anode1(display1),
	 .segment_anode2(display2)
	);

endmodule