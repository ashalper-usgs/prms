## See
## https://www.gnu.org/software/automake/manual/html_node/Built-Sources-Example.html

bin_PROGRAMS = prms

prms_SOURCES = basin.f90 basin_sum.f90 basin_summary.f90		\
               call_modules.f90 cascade.f90 ccsolrad.f90		\
               climate_hru.f90 climateflow.f90 convert_params.f90	\
               ddsolrad.f90 dynamic_param_read.f90 frost_date.f90	\
               gwflow.f90 ide_dist.f intcp.f90 map_results.f90		\
               muskingum.f90 muskingum_lake.f90 nhru_summary.f90	\
               nsegment_summary.f90 nsub_summary.f90 obs.f90		\
               potet_hamon.f90 potet_hs.f90 potet_jh.f90		\
               potet_pan.f90 potet_pm.f90 potet_pm_sta.f90		\
               potet_pt.f90 precip_1sta_laps.f90 precip_dist2.f90	\
               prms_summary.f90 prms_time.f90 routing.f90		\
               setup_param.f90 snowcomp.f90 soilzone.f90 soltab.f90	\
               srunoff.f90 strmflow.f90 strmflow_in_out.f90		\
               subbasin.f90 temp_1sta_laps.f90 temp_dist2.f90		\
               transp_frost.f90 transp_tindex.f90 utils_prms.f90	\
               water_balance.f90 water_use_read.f90			\
               write_climate_hru.f90 xyz_dist.f

prms_LDADD = ../mmf/libmmf.a

nodist_prms_SOURCES = prms_module.mod

BUILT_SOURCES = climateflow.mod prms_basin.mod prms_cascade.mod		\
                prms_climate_hru.mod prms_gwflow.mod prms_intcp.mod	\
                prms_module.mod prms_obs.mod prms_potet_hamon.mod	\
                prms_potet_hs.mod prms_potet_jh.mod prms_potet_pm.mod	\
                prms_potet_pt.mod prms_routing.mod prms_snow.mod	\
                prms_soilzone.mod prms_soltab.mod prms_srunoff.mod	\
                prms_time.mod prms_transp_tindex.mod			\
                prms_transp_frost.mod prms_water_use.mod

CLEANFILES = *.mod

prms_module.mod: call_modules.f90 Makefile
	$(FC) -c $<

climateflow.mod: climateflow.f90 prms_time.mod Makefile
	$(FC) -c $<

prms_basin.mod: basin.f90 prms_module.mod Makefile
	$(FC) -c $<

prms_gwflow.mod: gwflow.f90 prms_intcp.mod prms_srunoff.mod prms_soilzone.mod Makefile
	$(FC) -c $<

prms_srunoff.mod: srunoff.f90 prms_snow.mod Makefile
	$(FC) -c $<

prms_time.mod: prms_time.f90 prms_basin.mod prms_module.mod Makefile
	$(FC) -c $<

# these have regular names, so we can use a static pattern rule
prms_cascade.mod prms_obs.mod prms_soilzone.mod prms_routing.mod prms_soltab.mod prms_potet_hamon.mod prms_potet_hs.mod prms_potet_jh.mod prms_potet_pm.mod prms_potet_pt.mod prms_transp_tindex.mod prms_transp_frost.mod: prms_%.mod: %.f90 Makefile
	$(FC) -c $<

prms_intcp.mod: intcp.f90 prms_obs.mod prms_water_use.mod Makefile
	$(FC) -c $<

prms_water_use.mod: water_use_read.f90 Makefile
	$(FC) -c $<

prms_snow.mod: snowcomp.f90 Makefile
	$(FC) -c $<

prms_climate_hru.mod: climate_hru.f90 prms_soltab.mod Makefile
	$(FC) -c $<
