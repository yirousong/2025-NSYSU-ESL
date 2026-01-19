#Specify Design Libraries
set sh_source_uses_search_path true
set search_path "/cad/CBDK/CBDK_TSMC90GUTM_Arm_f1.0/CIC/SynopsysDC/db/ $search_path"
set target_library "slow.db fast.db typical.db"
set link_library "* $target_library"
set symbol_library "tsmc090.sdb generic.sdb"
set power_enable_analysis true
set power_analysis_mode averaged
set power_report_leakage_breakdowns true
#Read File
read_verilog ./GCD_syn.v
current_design GCD
link
read_sdc ./GCD_syn.sdc
read_sdf ./GCD_syn.sdf
read_vcd -strip_path testbench/GCD ./GCD_syn.vcd
#Verify
check_timing
update_timing
check_power
update_power
#Report Power
report_power -hierarchy > report_power_average_vcd.txt
exit
