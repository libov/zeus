int swimming() {

    // plug in F2c values for the vertex measurement
    const unsigned n_points_vtx = 18;
    Double_t    f2_vtx[n_points_vtx] = {0.1671930, 0.1404440, 0.2033370, 0.1779830, 0.3307380, 0.2674600, 0.2283320, 0.1916020, 0.1449490, 0.3442580, 0.2852130, 0.2176140, 0.1615690, 0.2968800, 0.1918290, 0.1036390, 0.1746280, 0.0744136};

    // plug in F2c values for the combined charm measurement
    const unsigned n_points_charm_combination = 52;
    Double_t    f2_charm_combination[n_points_charm_combination] = {0.1008140, 0.0807188, 0.0678170, 0.0613600, 0.0499999, 0.1633090, 0.1255860, 0.1029030, 0.0730416, 0.1878050, 0.1708200, 0.1468290, 0.1255370, 0.1072210, 0.0845146, 0.2503570, 0.2238680, 0.1945660, 0.1670190, 0.1325850, 0.1012620, 0.2892440, 0.2565540, 0.2212490, 0.1828670, 0.1446880, 0.1190040, 0.3380860, 0.3049000, 0.2479230, 0.2003580, 0.1786320, 0.1385560, 0.1134930, 0.3270330, 0.2836770, 0.2312530, 0.1876510, 0.1463080, 0.1004060, 0.3554870, 0.2877540, 0.2203300, 0.1572960, 0.0816923, 0.2609560, 0.1479530, 0.1932370, 0.0970483, 0.1761250, 0.0823545, 0.0536408};

    // print them out to see whether everything is ok
    for (int i=0; i<n_points_vtx; i++) {
        cout << "point " << i << ", F2= " << f2_vtx[i] << endl;
    }
    cout << endl;
    for (int i=0; i<n_points_charm_combination; i++) {
        cout << "point " << i << ", F2= " << f2_charm_combination[i] << endl;
    }

    // calculate swimming factors
    Double_t swimming_factors[n_points_vtx][n_points_charm_combination];
    for (int i=0; i<n_points_vtx; i++) {
        for (int j=0; j<n_points_charm_combination; j++) {
            swimming_factors[i][j] = f2_charm_combination[j]/f2_vtx[i];
        }
    }

    // print them out
    cout << endl;
    for (int i=0; i<n_points_vtx; i++) cout << i << " ";
    cout << endl;

    for (int j=0; j<n_points_charm_combination; j++) {
        for (int i=0; i<n_points_vtx; i++) {
            cout << swimming_factors[i][j] << " ";
        }
        cout << endl;
    }

    // finished
    return 0;
}