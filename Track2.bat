set NCUINCLUDE=D:/Source/NCUCodeMerge/Track2_NCU_Code/src/include/
set NCUBASE=D:/Source/NCUCodeMerge/Track2_NCU_Code/src
set TRACK=Track2
set ARGS=-c -std=c90 -Wno-macro-redefined -Wno-return-type -Wno-implicit-function-declaration -nostdinc -isystem stdincludes -I %NCUINCLUDE% -Xclang -ast-dump=json -ferror-limit=9999


set DIR=haldriver/comm_hayes_modem
set FILE=commdial.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_hayes_modem
set FILE=test_comm_modem.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_net_tcpip
set FILE=commsock.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_net_tcpip
set FILE=test_comm_tcpip.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_net_tcpip6
set FILE=commsock6.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_net_tcpip6
set FILE=test_comm_tcpip6.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_scup_485
set FILE=comm_scup_485.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_std_serial
set FILE=commserial.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_std_serial
set FILE=test_comm_serial.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_virtual_port
set FILE=commvirtual.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/comm_virtual_port
set FILE=test_comm_virtual.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/ui_base
set FILE=lcd_font_lib.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=haldriver/ui_base
set FILE=lcd_interface.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/applog
set FILE=appfilelog.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/applog
set FILE=appflashlog.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/applog
set FILE=applog.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/applog
set FILE=test_applog.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/app_service
set FILE=app_service.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/comm_base
set FILE=halcomm.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/comm_base
set FILE=test_comm_speed.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/comm_base
set FILE=test_hal_comm.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/config_parser
set FILE=cfg_parser.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/config_parser
set FILE=cfg_reader.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/data_exchange
set FILE=data_exchange.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/data_exchange
set FILE=system_net_info.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/data_exchange
set FILE=test_data_exchange.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/data_mgmt
set FILE=his_data.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/data_mgmt
set FILE=test_data_mng.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=new.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=pubfunc.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=run_mutex.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=run_queue.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=run_thread.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=run_timer.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/publib
set FILE=test_pub_lib.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/security_manage
set FILE=test_user_manage.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=lib/security_manage
set FILE=user_manage.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=log
set FILE=log_read.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=cfg_loader.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=cfg_loadrun.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=cfg_load_solution.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=cfg_load_stdbasic.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=cfg_load_stdequip.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/config_mgmt
set FILE=test_cfg.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_ctrl_cmd.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_data_process.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_data_sample.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_exp_eval.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_mon_init.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_mon_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_mon_unload.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=equip_sn_convert.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/equip_mon
set FILE=test_equip_mon.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/main
set FILE=main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/main
set FILE=main_args.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/main
set FILE=service_mgr.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/main
set FILE=sig_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/main
set FILE=watch_dog.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/splash
set FILE=acu_splash.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/splash
set FILE=splash_args.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/splash
set FILE=splash_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/time_sync
set FILE=test_time_sync.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=mainapp/time_sync
set FILE=time_sync.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=maintenance
set FILE=debug_lcd_msg.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=maintenance
set FILE=debug_s_p.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=maintenance
set FILE=msp_args.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_converter.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_dcem.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_inverter.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_mppt.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_rectifier.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_sampler_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_smdu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_smduh.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_smduhh.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_smdup.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=can_smtemp.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/can_sampler
set FILE=NA_battery.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/eem_csu
set FILE=eem_csu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/i2c_sampler
set FILE=i2c_sampler_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/main_board
set FILE=main_board.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_comm.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_FCUP.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_hdu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_iplu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_large_dus.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_modbus.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_report.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_slaves.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_smac.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_smbat.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_smbrc.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_smdu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/rs485_sampler
set FILE=rs485_smio.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=sampler/sampler_base
set FILE=win32api_stub.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service
set FILE=cgi_startacu.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=alarm_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=command_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=config_builder.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=eem_state_machine.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=esr_utility.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=frame_analysis.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=linklayer_manager.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=service_provider.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=soc_state_machine.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/eem_soc
set FILE=test_esr.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_batt_cap.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_batt_history.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_batt_mgmt.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_boost_charge.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_discharge.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_dsl_test.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_engy_sav.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_estop_eshutdown.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_float_charge.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_init_equip.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_lvd.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_main_switch.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_picket.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_power_split.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_pri_cfg.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_rect_list.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_rect_redund.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_run_info.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_sig_value.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_test.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_test_log.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gc_timer.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=gen_ctl.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/gen_ctl
set FILE=pub_list.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui
set FILE=problem_qt_fifo.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui
set FILE=qt_fifo.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_ack_dlg.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_alarms_screen.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_default_screen.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_item_handle.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_language_screen.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_main.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_menu_screen.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_password_dlg.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=lcd_signals_screen.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/lcd_ui_mini
set FILE=test_lcd_module.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/mail
set FILE=base64.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/mail
set FILE=mail.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/maintenance_intf
set FILE=debug_maintn.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/maintenance_intf
set FILE=test_mp.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=command_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=config_builder.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=frame_analysis.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=linklayer_manager.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=modbus_state_machine.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=modbus_utility.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/modbus
set FILE=service_provider.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/plc
set FILE=plc.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/plc
set FILE=test_plc.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/simple_service
set FILE=simple_service.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/sms
set FILE=SMS.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmpv3_agent
set FILE=powerMIB.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmpv3_agent
set FILE=snmpd.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmpv3_agent
set FILE=snmp_agent.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmp_agent
set FILE=powerMIB.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmp_agent
set FILE=snmpd.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/snmp_agent
set FILE=snmp_agent.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=appmain.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgivars.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_filemanage.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_maintenance.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_multilanguage.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_passwd_netscape.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_pub.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_query.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_query_netscape.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_realtime.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_setting.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=cgi_suicide_timer.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=communicate.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=control_command.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=test_cgi.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_control.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_geteem.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_getip.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_getlang.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_getnms.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_gettime.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_reset.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_seteem.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_setip.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_setlang.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_setnms.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_ui
set FILE=web_net_settime.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=appmain.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgivars.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_filemanage.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_filemanage_ESNA.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_pub.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_query.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_setting.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=cgi_suicide_timer.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=control_command.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=jsonFile.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=web_egy_sav.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=web_rw_flash.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/web_user
set FILE=web_user.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=alarm_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=command_handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=config_builder.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=frame_analysis.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=linklayer_manager.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=service_provider.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=test_ydn.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=ydn_state_machine.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=service/ydn23
set FILE=ydn_utility.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=systemhandler
set FILE=handler.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

set DIR=systemhandler
set FILE=smain.c
clang  %ARGS% %NCUBASE%/%DIR%/%FILE% > BuildDir/%TRACK%/%DIR%/%FILE%.json 2> BuildDir/%TRACK%/%DIR%/%FILE%.errors
cp %NCUBASE%/%DIR%/%FILE% BuildDir/%TRACK%/%DIR%

rem set NCUINCLUDE=D:/Source/NCUCodeMerge/Track3_NCU_Code/G3/src/include/
rem set NCUBASE=D:/Source/NCUCodeMerge/Track3_NCU_Code/G3/src
rem set TRACK=Track3
rem clang -c -std=c90 -Wno-macro-redefined -Wno-return-type -Wno-implicit-function-declaration -nostdinc -isystem stdincludes -I %NCUINCLUDE% -Xclang -ast-dump=json -ferror-limit=9999 %NCUBASE%/%1/%2 > BuildDir/%TRACK%/%2.json 2> BuildDir/%TRACK%/%2.errors
