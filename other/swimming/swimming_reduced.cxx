int swimming_reduced() {

    // plug in F2c values for the vertex measurement
    const unsigned n_points_vtx = 18;
    Double_t    f2_vtx[n_points_vtx] = {0.166087, 0.13986, 0.202679, 0.177834, 0.312367, 0.264336, 0.228046, 0.190666, 0.144611, 0.329659, 0.2809, 0.216516, 0.161339, 0.287093, 0.19105, 0.10342, 0.16939, 0.0742414};

    // plug in F2c values for the combined charm measurement
    const unsigned n_points_charm_combination = 52;
    Double_t    f2_charm_combination[n_points_charm_combination] = {0.0960349, 0.0801324, 0.0678521, 0.0611367, 0.0499133, 0.155467, 0.124508, 0.103222, 0.0728377, 0.182634, 0.16887, 0.146648, 0.124837, 0.107494, 0.0853296, 0.241135, 0.222431, 0.193638, 0.165237, 0.130317, 0.102698, 0.276569, 0.253433, 0.218064, 0.181988, 0.143884, 0.11306, 0.32076, 0.296868, 0.247462, 0.200434, 0.177596, 0.138724, 0.114674, 0.318009, 0.279872, 0.230507, 0.188235, 0.14661, 0.0989443, 0.332484, 0.281621, 0.218823, 0.157189, 0.0810732, 0.254773, 0.147584, 0.190034, 0.0969699, 0.169821, 0.0819446, 0.052723};

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