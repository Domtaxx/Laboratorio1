module BCD_to_seven_segment(
    input logic [3:0] bcd_input,
    output logic [6:0] segment
);

    // BCD to Seven-Segment Decoder Truth Table
    //   ABCD => SEG[6:0]
    //   0000 => 0b1000000 (0)
    //   0001 => 0b1111001 (1)
    //   0010 => 0b0100100 (2)
    //   ...  => ...

    always_comb begin
        case (bcd_input)
            4'b0000: segment = 7'b1000000;
            4'b0001: segment = 7'b1111001;
            4'b0010: segment = 7'b0100100;
				4'b0011: segment = 7'b0110000;
				4'b0100: segment = 7'b0011001;
				4'b0101: segment = 7'b0010010;
				4'b0110: segment = 7'b0000010;
				4'b0111: segment = 7'b1111000;
				4'b1000: segment = 7'b0000000;
				4'b1001: segment = 7'b0011000;
            
            default: segment = 7'b1111111; // Turn off the display for unknown inputs
        endcase
    end

endmodule