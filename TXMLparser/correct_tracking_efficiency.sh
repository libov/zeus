export CN_VERSION=v06

systematics --file tracking_map_charm_correction_2.77 --correct_cross_sections --cross_sections_XMLfile results.full.forCHARM2.98.2.0405e06e07p.v02.true05e06e0607p.xml
systematics --file tracking_map_beauty_correction_2.78 --correct_cross_sections --cross_sections_XMLfile results.full2.99.2.0405e06e07p.v02.true05e06e0607p.xml

export CN_VERSION=v02
