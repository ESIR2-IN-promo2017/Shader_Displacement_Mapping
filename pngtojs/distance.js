
function distance() {

 	var nb_layers = 8;
 	var height = 1;
 	var width = 1;
 	//
 	// La variable img n'est pas correcte !
 	// new Array(nb) créé un tableau de nb éléments
 	var img = new Array(1);
 	img[0] = new Array(1);
 	var L = [];


 	// Init avec les valeurs max
 	for(h=0; h<nb_layers; ++h)
    {
        L[h] = [];
        for(i = 0; i < height*width; ++i) {
            L[h][i] = Number.MAX_VALUE;
        }
    }

    for(i = 0; i < height; ++i) {
        for(j = 0; j < width; ++j) {
            var h_max = Math.floor( img[i][j]* nb_layers / 255.0);
            for( h = 0; h < h_max; ++h)
                L[h][i*width+j] = 0;
        }
    }

    for( h = 0; h < nb_layers; ++h) {
        for( i = 0; i < height; ++i) {
            for( j = 0; j < width; ++j)
            {
                var val = L[h][i*width + j];
                var valh = (h > 0)? L[h-1][i*width+j] + 1 : val;
                var valj = (j > 0)? L[h][i*width+(j-1)] + 1 : val;
                var vali = (i > 0)? L[h][(i-1)*width+j] + 1 : val;

                L[h][i*width + j] = Math.min(Math.min(val, valh), Math.min(valj, vali));
            }
        }
    }

    for( h = nb_layers - 1; h >= 0; --h) {
        for( i = height - 1; i >= 0; --i) {
            for( j = width - 1; j >= 0; --j) {
                var val = L[h][i*width + j];
                var valh = (h < nb_layers - 1)? L[h+1][i*width+j] + 1 : val;
                var valj = (j < width - 1)? L[h][i*width + (j+1)] + 1 : val;
                var vali = (i < height - 1)? L[h][(i+1)*width+ j] + 1 : val;

                L[h][i*width + j] = Math.min(Math.min(val, valh), Math.min(valj, vali));
            }
        }
    }
 	

}
