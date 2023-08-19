	component test_count is
		port (
			clk_clk                                  : in  std_logic                    := 'X';             -- clk
			reset_reset_n                            : in  std_logic                    := 'X';             -- reset_n
			led_pio_external_connection_export       : out std_logic_vector(7 downto 0);                    -- export
			seven_seg_pio_external_connection_export : out std_logic_vector(6 downto 0);                    -- export
			button_pio_external_connection_export    : in  std_logic_vector(3 downto 0) := (others => 'X')  -- export
		);
	end component test_count;

	u0 : component test_count
		port map (
			clk_clk                                  => CONNECTED_TO_clk_clk,                                  --                               clk.clk
			reset_reset_n                            => CONNECTED_TO_reset_reset_n,                            --                             reset.reset_n
			led_pio_external_connection_export       => CONNECTED_TO_led_pio_external_connection_export,       --       led_pio_external_connection.export
			seven_seg_pio_external_connection_export => CONNECTED_TO_seven_seg_pio_external_connection_export, -- seven_seg_pio_external_connection.export
			button_pio_external_connection_export    => CONNECTED_TO_button_pio_external_connection_export     --    button_pio_external_connection.export
		);

