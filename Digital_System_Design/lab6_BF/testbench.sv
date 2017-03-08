
// Brian Faure
// testbench.sv

module testbench();
  
  logic CLOCK_50;
  logic sw;
  wire [6:0] HEX0,HEX1,HEX2,HEX3,HEX4,HEX5,HEX6,HEX7;
  
  lab6_BF test(.*);
  
  logic [6:0] d_0 = 7'b1000000;
  logic [6:0] d_1 = 7'b1111011;
  logic [6:0] d_2 = 7'b0100100;
  logic [6:0] d_3 = 7'b0110000;
  logic [6:0] d_4 = 7'b0011001;
  logic [6:0] d_5 = 7'b0010010;
  logic [6:0] d_6 = 7'b0000010;
  logic [6:0] d_7 = 7'b1111000;
  logic [6:0] d_8 = 7'b0000000;
  logic [6:0] d_9 = 7'b0011000;
  logic [6:0] d_a = 7'b0001000;
  logic [6:0] d_b = 7'b0000011;
  logic [6:0] d_c = 7'b0100111;
  logic [6:0] d_d = 7'b0100001;
  logic [6:0] d_e = 7'b0000110;
  logic [6:0] d_f = 7'b0001110;
  
  string out = "";
  
  function void print(string s);
    begin
      $display(s);
    end
  endfunction
  
  function string get_value(logic [6:0] inputt);
    begin
      case(inputt)
        d_0: return "0";
        d_1: return "1";
        d_2: return "2";
        d_3: return "3";
        d_4: return "4";
        d_5: return "5";
        d_6: return "6";
        d_7: return "7";
        d_8: return "8";
        d_9: return "9";
        d_a: return "a";
        d_b: return "b";
        d_c: return "c";
        d_d: return "d";
        d_e: return "e";
        d_f: return "f";
        default: return "-";
      endcase
    end
  endfunction
  
  function void print_outputs();
    begin
      out = "--> ";
      out = {out,get_value(HEX0)};
      out = {out,get_value(HEX1)};
      out = {out,get_value(HEX2)};
      out = {out,get_value(HEX3)};
      out = {out,get_value(HEX4)};
      out = {out,get_value(HEX5)};
      out = {out,get_value(HEX6)};
      out = {out,get_value(HEX7)};
      print(out);
    end
  endfunction
  
  task toggle_clock;
    begin
      
      #1 CLOCK_50 = !CLOCK_50;
      #1 CLOCK_50 = !CLOCK_50;
      
    end
  endtask
    
  task simulate(integer n);
    begin
      
      sw = 0;
      CLOCK_50 = 0;
      
      for(integer i=0; i<n; i++)
        begin
          toggle_clock();
          #2 print_outputs();
        end
      
    end
  endtask
  
  initial
    begin
      simulate(8);
      print("--> TOGGLING USER PAUSE");
      #2 sw = 1;
      #2 simulate(5);
      print("--> TOGGLING USER PAUSE");
      sw = 0;
      #2 sw = 1;
      #2 simulate(8);
    end
endmodule
  