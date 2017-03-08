// Testbench for Lab 3

module testbench();
  
  logic clk, n, s, e, w, reset;
  logic win, d, s6, s5, s4, s3, s2, s1, s0;
  
  // The name of the module below (here it is 'lab_3_sdm), should be renamed to your top level module's name (where both FSMs are connected).
  // Make sure to match signal names else it will not work.
  
  lab3_BF adventuregame(.clk, .reset, .n, .s, .e, .w, 
                        .win, .d, .s6, .s5, .s4, .s3, .s2, .s1, .s0);

  // generate clock with 100 ns period
  initial
    forever begin
      clk = 0; #50; clk = 1; #50;
    end  
    
  // apply inputs
  initial begin 
    #10; // wait a bit so transitions don't occur on the clock edge
  
    // cycle 0: reset to Cave of Cacophony
    reset = 1;
    n = 0; s = 0; e = 0; w = 0;
    #100;
  
    // cycle 1: east to Twisty Tunnel
    reset = 0;
    e = 1;
    #100;
  
    // cycle 2: south to Rapid River
    e = 0;
    s = 1;
    #100;

    // cycle 2b: west to Secret Sword Stash
    s = 0;
    w = 1;
    #100;

    // cycle 2c: east to Rapid River
    w = 0;
    e = 1;
    #100;
  
    // cycle 3: east to Dragon's Den
    s = 0;
    e = 1;
    #100;
  
    // cycle 4: eaten by dragon
    s = 0;
    #100;
  end
    
endmodule