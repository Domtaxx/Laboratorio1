module tallernios
(
	input logic clk,
					rst_n,
	input logic[1:0] switch,
	output logic[6:0] display1,
	output logic[6:0] display2,
	output logic[6:0] display3,
	output logic[6:0] display4,
	output logic[6:0] display5,
	output logic[6:0] display6
);

	logic[7:0] seg_num;
	logic[7:0] ms_num;
	logic[7:0] min_num;
	

	platform plat
	(
		.clk_clk(clk),
		.pio_leds_0_external_connection_export(seg_num),
		.pio_ms_num_0_external_connection_export(ms_num),
		.pio_min_num_0_external_connection_export(min_num),
		.pio_switch_0_external_connection_export(switch),
		.reset_reset_n(rst_n)
	);
	

	two_seven_segment_displays(
    .decimal_number(seg_num),
    .segment_anode1(display1),
	 .segment_anode2(display2)
	);
	
	two_seven_segment_displays(
    .decimal_number(ms_num),
    .segment_anode1(display3),
	 .segment_anode2(display4)
	);
	
		two_seven_segment_displays(
    .decimal_number(min_num),
    .segment_anode1(display5),
	 .segment_anode2(display6)
	);

endmodule