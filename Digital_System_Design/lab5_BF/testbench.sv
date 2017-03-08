
// Brian Faure
// testbench.sv

module testbench();
  
  // Creating local variables
  logic	[2:0]	f;		// Input
  logic [31:0]	a,b;	// Inputs
  
  wire [31:0]	y;		// Output
  wire			zero;	// Output
  
  wire [31:0]	predicted_y;	// test vector
  wire			predictred_zero;// test vector
  
  integer 		f_int;			// Used to print decimal
  integer		a_int, b_int;	// 
  integer		y_int;			// 
  integer		zero_int;		// 
  
  integer 		predicted_y_int;	// Used to compare
  integer		predicted_zero_int;	// Used to compare
  int			correct_output;
  
  string 		file_buffer;	// file read buffer
  integer		vector_file; 	// file handler
  integer		scan_file;		// file handler
  string		temp;			// file read buffer substring

  // Hook up pins to an alu chip
  alu alu_chip(.*);
  
  // Creating operation state encodings
  typedef enum logic [2:0] {s0 = 3'b000, // A AND B
                            s1 = 3'b001, // A OR B
                            s2 = 3'b010, // A + B
                            s3 = 3'b011, // not used
                            s4 = 3'b100, // A AND B'
                            s5 = 3'b101, // A OR B'
                            s6 = 3'b110, // A - B
                            s7 = 3'b111}  // SLT (Set less than)
  statetype;
  
  // Initial execution step
  initial
    begin
      
      $display("\n\nBeginning testbench...\n");
      vector_file = $fopen("alu.tv", "r"); // Open alu.tv
      
      if (vector_file == 0)
        begin
          $display("Could not find vector file");
          $finish;
      	end
      
      main(); // Call the main method
      $display("\nEnding testbench.\n\n");
    end
  
  // Main method
  task main;
    begin
      // Iterate through each line of file (22 lines)
      for(int i=0; i<22; i++)
        begin
          
          #10 get_vector(); 	// Read in next vector
          #10 check_output();	// Check the output for correctness
          
        end
    end
  endtask

  // Reads in a single test vector
  function void get_vector;
    begin
      // Pull in line of file
      scan_file = $fscanf(vector_file, "%s\n", file_buffer);
      // Display the vector
      $display("Current file vector: %0s, Buffer length: %0d", file_buffer, file_buffer.len());
      // Parse the vector string
      parse_buffer();
    
    end
  endfunction
  
  // Parses values in string file_buffer and assigns
  // them to a, b, f, predicted_y_int, & predicted_zero_int
  function void parse_buffer;
    begin
      // Order in vector is as follows f_a_b_y_zero
      
      // Get f
      temp 	= file_buffer.substr(0,0);
      f		= temp.atohex();
      temp	= "";
      
      // Get a
      temp 	= file_buffer.substr(2,9);
      a		= temp.atohex();
      temp 	= "";
      
      // Get b
      temp 	= file_buffer.substr(11,18);
      b 	= temp.atohex();
      temp 	= "";
      
      // Get y
      temp 				= file_buffer.substr(20,27);
      predicted_y_int 	= temp.atohex();
      temp 				= "";
      
      // Get zero
      temp 					= file_buffer.substr(29,29);
      predicted_zero_int	= temp.atohex();
      temp 					= "";
      
    end
  endfunction
  
  // Checks the current output values against their
  // test vector predicted values.
  function void check_output;
    begin
      
      y_int 			= y;
      zero_int 			= zero;
      correct_output 	= 1;
      
      if (y_int != predicted_y_int)
        begin
          correct_output = 0;
          $display("y output does not match its prediction, y = %0d, predicted_y = %0d", y_int, predicted_y_int);
        end
      
      if (zero_int != predicted_zero_int)
        begin
          correct_output = 0;
          $display("zero output does not match its prediction, zero = %0d, predicted_zero = %0d", zero_int, predicted_zero_int);
        end
      
      if (correct_output == 1)
        begin
          
          $display("Output matched test vector-predicted output.");
          
        end
    end
  endfunction
  
  // Helper to print all variables in decimal
  function void print_decimal;
    begin
      a_int 	= a;
      b_int 	= b;
      f_int 	= f;
      y_int 	= y;
      zero_int 	= zero;
      
      $display("A = %0d,	B = %0d,	f = %0d", a_int, b_int, f_int);
      $display("y = %0d, 	zero = %0d", y_int, zero_int);
      
    end
  endfunction
  
  // Helper to print all variables in binary
  function void print_binary;
    begin
      
      $display("A    	= ", a);
      $display("B    	= ", b);
      $display("f    	= ", f);
      $display("y    	= ", y);
      $display("zero	= ", zero); 
      
    end
  endfunction
  
endmodule