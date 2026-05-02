# HWPE integration in Pulpissimo for 6G algorithms

     Contents

## Testing   
The testing should be done using the hwpe-tb:  https://github.com/pulp-platform/hwpe-tb<br>
- Step1: Remove the mac_engine.sv module and paste the Verilog files that come from synthesizing the project in HlS<br>
- Step2: Go to the mac_fsm module and change the trans and line lengh size to agree with the expected number of inputs in each channel<br>
- Step3: Go to mac_top folder and paste the followingw here the mac engine interface would normally be:
  
   <pre id="code">
     cont i_engine (  
     .ap_clk           (clk_i),    
      .ap_rst           (rst_ni),          
      .a_i_valid        (a.valid),     
      .a_i_ready        (a.ready),  
      .a_i_data         (a.data ),  
      .a_i_strb         (a.strb),  
      .b_i_valid        (b.valid),  
      .b_i_ready        (b.ready),  
      .b_i_data         (b.data),  
      .b_i_strb         (b.strb),  
      .c_i_valid        (c.valid),  
      .c_i_ready        (c.ready),  
      .c_i_data         (c.data),  
      .c_i_strb         (c.strb),  
      .d_o_valid        (d.valid),  
      .d_o_ready        (d.ready),  
      .d_o_data         (d.data),  
      .d_o_strb         (d.strb),  
      .clear            (engine_ctrl.clear),  
      .enable           (engine_ctrl.enable),  
      .function_r       (engine_ctrl.simple_mul),  
      .start_r          (engine_ctrl.start),  
      .shift            (engine_ctrl.shift),  
      .len              (engine_ctrl.len),  
      .f_cnt            (engine_flags.cnt),  
      .f_valid	        (engine_flags.acc_valid)  
      );    
   </pre>  


