module button_debouncer (
    input wire button,
    output wire debounced_button
);

    reg [15:0] debounce_counter = 16'd0;
    reg prev_button_state = 1'b1;
    wire button_stable;

    assign button_stable = (debounce_counter == 16'd0);

    always @(posedge button) begin
        if (!button) begin
            if (prev_button_state && button_stable)
                debounce_counter <= 16'd5; // Set debounce time (adjust as needed)
            else
                debounce_counter <= debounce_counter - 1;
        end else begin
            debounce_counter <= 16'd0;
        end
        prev_button_state <= button;
    end

    assign debounced_button = button_stable && prev_button_state;

endmodule



