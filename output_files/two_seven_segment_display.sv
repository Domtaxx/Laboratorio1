module two_seven_segment_displays(
    input logic [7:0] decimal_number,
    output logic [6:0] segment_anode1,
    output logic [6:0] segment_anode2
    //output logic display_enable
);

    logic [3:0] bcd_digit1; // 1st digit
    logic [3:0] bcd_digit2; // 2nd digit

    assign bcd_digit1 = decimal_number[3:0];
    assign bcd_digit2 = decimal_number[7:4];

    // BCD to Seven-Segment Decoder Instances
    BCD_to_seven_segment bcd_to_7seg1(
        .bcd_input(bcd_digit1),
        .segment(segment_anode1)
    );

    BCD_to_seven_segment bcd_to_7seg2(
        .bcd_input(bcd_digit2),
        .segment(segment_anode2)
    );

endmodule
