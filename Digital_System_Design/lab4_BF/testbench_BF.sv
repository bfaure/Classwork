
// Brian Faure
// testbench_BF.sv

module testbench_BF();
  
  logic 		clk, reset;
  logic			left, right;
  
  wire			la, lb, lc;
  wire			ra, rb, rc;
  
  // Create taillights module and connect ports
  lab4_BF taillights(.*);
  
  // Generate clock
  always
    begin
      #1 clk = ~clk;
    end
  
  initial
    begin
      $display("\n\nBeginning testbench...");
      main(); // Call the main method
      $display("Ending testbench.\n\n");
    end
  
  // Prints out the tail light states
  function void print_lights;
    begin
      $display("	--> lc=%0d, lb=%0d, la=%0d, ra=%0d, rb=%0d, rc=%0d",
               lc,lb,la,ra,rb,rc);
    end
  endfunction
  
  function void set_left;
    begin
      $display("Setting: left=1, right=0, reset=0");
      left 	= 1;
      right = 0;
      reset = 0;
    end
  endfunction
  
  function void set_right;
    begin
      $display("Setting: left=0, right=1, reset=0");
      right	= 1;
      left	= 0;
      reset	= 0;
    end
  endfunction
  
  function void set_none;
    begin
      $display("Setting: left=0, right=0, reset=0");
      right	= 0;
      left	= 0;
      reset	= 0;
    end
  endfunction
  
  function void set_reset;
    begin
      $display("Setting: left=0, right=0, reset=1");
      right	= 0;
      left	= 0;
      reset	= 1;
    end
  endfunction
  
  task main;
    begin
      
      clk = 0;
      print_lights(); 		// xxx xxx
      
      set_reset();			// Setting: left=0, right=0, reset=0
      #2 print_lights();	// 000 000
      
      
      set_left();			// Setting: left=1, right=0, reset=0
      #2 print_lights();	// 001 000
      #2 print_lights();	// 011 000
      #2 print_lights();	// 111 000
      #2 print_lights();	// 001 000
      #2 print_lights();	// 011 000
      #2 print_lights();	// 111 000
      
      set_none();			// Setting: left=0, right=0, reset=0
      #2 print_lights();	// 000 000
      
      set_right();			// Setting: left=0, right=1, reset=0
      #2 print_lights();	// 000 100
      #2 print_lights();	// 000 110
      #2 print_lights();	// 000 111
      #2 print_lights();	// 000 100
      #2 print_lights();	// 000 110
      #2 print_lights();	// 000 111
      
      set_reset();			// Setting: left=0, right=0, reset=1
      #2 print_lights();	// 000 000
      
    end
    
  endtask
endmodule



