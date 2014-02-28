# note, the final analysis for charm is 2.98.2 while here 2.111.2 is used. this is because the binning for one of the plots (significance no mass restriction) had to be changed so the analysis needed to be rerun

./plotter -b full.forCHARM -v 2.111.2 -d -s --config_file F2bc_paper_charm --no_indices

./plotter -b full -v 2.99.2 -d -s --config_file F2bc_paper_beauty --no_indices

./plotter -b full.forCHARM -v 2.111.2 -d -s --config_file F2bc_paper_significance

./plotter -b full.forCHARM -v 2.111.2 -d -s --config_file F2bc_paper_significance_mirrored
