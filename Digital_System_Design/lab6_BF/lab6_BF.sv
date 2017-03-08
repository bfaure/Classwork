
// Brian Faure
// lab6_BF.sv


// first param should be CLOCK_50
// second param should be SW[0]

module lab6_BF(input logic      CLOCK_50,
               input logic      sw,
               output logic [6:0]   HEX0,HEX1,HEX2,
                          HEX3,HEX4,HEX5,
                          HEX6,HEX7);
  
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
  
  logic [6:0] aa;
  logic [6:0] bb;
  logic [6:0] cc;
  logic [6:0] dd;
  logic [6:0] ee;
  logic [6:0] ff;
  logic [6:0] gg;
  logic [6:0] hh;
  
  integer current_state       = 0;
  integer clock_modulus       = 1;
  //integer clock_modulus       = 50000000;
  integer current_clock_increment = 0;
  integer should_rotate       = 1;
  integer user_pause        = 0;

  // Triggered on every clock edge (50MHz)
  always @(posedge CLOCK_50)
    begin    
      //print("Here 1");
      current_clock_increment   += 1;
      should_rotate       = 0;
      
      if ((current_clock_increment % clock_modulus) == 0)
        begin
          //print("Here 7");
          should_rotate       = 1;
          current_clock_increment   = 0;
          
          if (user_pause == 0)
            current_state ++;
          
          if (current_state == 16)
              current_state = 0;
        end
    end
  
  // Triggered if user clicks the pause button
  always @(posedge sw)
    begin
      
      //print("Here 2");
      if (user_pause == 0)  user_pause = 1;
      else          user_pause = 0;
    
    end
  
  function void set_outputs(logic [6:0] a, logic [6:0] b, logic [6:0] c,
                            logic [6:0] d, logic [6:0] e, logic [6:0] f,
                            logic [6:0] g, logic [6:0] h
                           );
    begin
      //print("Here 3");
      aa = a;
      bb = b;
      cc = c;
      dd = d;
      ee = e;
      ff = f;
      gg = g;
      hh = h;
    end
  endfunction
  
  function void set_state(integer state);
    begin
      case(current_state) 
        0:  set_outputs(d_0,d_1,d_2,d_3,d_4,d_5,d_6,d_7);
        1:  set_outputs(d_1,d_2,d_3,d_4,d_5,d_6,d_7,d_8);
        2:  set_outputs(d_2,d_3,d_4,d_5,d_6,d_7,d_8,d_9);
        3:  set_outputs(d_3,d_4,d_5,d_6,d_7,d_8,d_9,d_a);
        4:  set_outputs(d_4,d_5,d_6,d_7,d_8,d_9,d_a,d_b);
        5:  set_outputs(d_5,d_6,d_7,d_8,d_9,d_a,d_b,d_c);
        6:  set_outputs(d_6,d_7,d_8,d_9,d_a,d_b,d_c,d_d);
        7:  set_outputs(d_7,d_8,d_9,d_a,d_b,d_c,d_d,d_e);
        8:  set_outputs(d_8,d_9,d_a,d_b,d_c,d_d,d_e,d_f);
        9:  set_outputs(d_9,d_a,d_b,d_c,d_d,d_e,d_f,d_0);
        10: set_outputs(d_a,d_b,d_c,d_d,d_e,d_f,d_0,d_1);
        11: set_outputs(d_b,d_c,d_d,d_e,d_f,d_0,d_1,d_2);
        12: set_outputs(d_c,d_d,d_e,d_f,d_0,d_1,d_2,d_3);
        13: set_outputs(d_d,d_e,d_f,d_0,d_1,d_2,d_3,d_4);
        14: set_outputs(d_e,d_f,d_0,d_1,d_2,d_3,d_4,d_5);
        15: set_outputs(d_f,d_0,d_1,d_2,d_3,d_4,d_5,d_6);
        default: set_outputs(d_0,d_1,d_2,d_3,d_4,d_5,d_6,d_7);
      endcase
    end
  endfunction
  
  always_comb
    begin
      
      //print("Here 4");
      if (should_rotate==1)       
          set_state(current_state);
      else
        set_state(current_state-1);
    end
  
    function void print(string s);
      begin
        $display(s);
      end
  endfunction
  
  assign HEX0 = aa;
  assign HEX1 = bb;
  assign HEX2 = cc;
  assign HEX3 = dd;
  assign HEX4 = ee;
  assign HEX5 = ff;
  assign HEX6 = gg;
  assign HEX7 = hh;
  
endmodule
  
  
  
  
  

  
  
  