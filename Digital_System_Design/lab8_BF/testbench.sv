
// Brian Faure
// testbench.sv

module testbench();
  
  parameter N = 64;
  parameter M = 6;
  
  logic [N-1:0] input_bits;
  logic [M-1:0] shift_pattern;
  logic [N-1:0] output_bits;
  
  lab8_BF #(.N(N), .M(M)) test(.*);
  
  integer num_tests = 15;
  integer init_value = 7;
  
  initial
    begin
      $display("\n\nBeginning testbench...");
      main();
      $display("Ending testbench.\n\n");
    end
  
  task main;
    begin
      #10 $display("Inside main.");
      simulate();
    end
  endtask
  
  task simulate;
    begin
      input_bits = init_value;
      shift_pattern = 0;
      #10 print();
      
      for (int i=0; i<num_tests; i++)
        begin
          shift_pattern++;
          #10 print();
        end
    end
  endtask
  
  function void print;
    begin
      $display("--> Input bits:     %b", input_bits);
      $display("--> Shift pattern:  %b", shift_pattern);
      $display("--> Output bits:  %b", output_bits);
    end
  endfunction
  
endmodule
      