
set PATH=
call C:/AMDDesignTools/2025.2/Vivado/bin/xelab xil_defaultlib.apatb_cpu_top glbl -Oenable_linking_all_libraries  -prj cpu.prj -L smartconnect_v1_0 -L axi_protocol_checker_v1_1_12 -L axi_protocol_checker_v1_1_13 -L axis_protocol_checker_v1_1_11 -L axis_protocol_checker_v1_1_12 -L xil_defaultlib -L unisims_ver -L xpm  -L floating_point_v7_1_21 -L floating_point_v7_0_26 --lib "ieee_proposed=./ieee_proposed" -s cpu 
call C:/AMDDesignTools/2025.2/Vivado/bin/xsim --noieeewarnings cpu -tclbatch cpu.tcl 

