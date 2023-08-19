
module test_count (
	clk_clk,
	reset_reset_n,
	led_pio_external_connection_export,
	seven_seg_pio_external_connection_export,
	button_pio_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	led_pio_external_connection_export;
	output	[6:0]	seven_seg_pio_external_connection_export;
	input	[3:0]	button_pio_external_connection_export;
endmodule
