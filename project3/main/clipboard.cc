W[j] = ( sin(k_x[j]*binsize/2.0 ) / (k_x[j]*binsize/2.0 )    ) * ( sin(k_x[j]*binsize/2.0 ) / (k_x[j]*binsize/2.0 )   ) 
     * ( sin(k_y[j]*binsize/2.0 ) / (k_y[j]*binsize/2.0 )    )*  ( sin(k_y[j]*binsize/2.0 ) / (k_y[j]*binsize/2.0 )    ) 
     * ( sin(k_z[j]*binsize/2.0 ) / (k_z[j]*binsize/2.0 )    ) * ( sin(k_z[j]*binsize/2.0 ) / (k_z[j]*binsize/2.0 )    )                    ;

 if (k_x[j]==0) {W_x[j] =1;} else if (k_x[j] !=0){ W_x[j]= ( sin(k_x[j]*binsize*0.5 ) / (k_x[j]*binsize*0.5 )        ) * ( sin(k_x[j]*binsize*0.5 ) / (k_x[j]*binsize*0.5 )   )  ;}
105                 if (k_y[j]==0){ W_y[j] =1;} else if (k_y[j] !=0) { W_y[j] =  ( sin(k_y[j]*binsize*0.5 ) / (k_y[j]*binsize*0.5     )    )*  ( sin(k_y[j]*binsize*0.5 ) / (k_y[j]*binsize*0.5 )    )  ;}
106                 if (k_z[j]==0) {W_z[j]=1;} else if (k_z[j] !=0) { W_z[j] = ( sin(k_z[j]*binsize*0.5 ) / (k_z[j]*binsize*0.5 )        ) * ( sin(k_z[j]*binsize*0.5 ) / (k_z[j]*binsize*0.5 )    ) ;}
 
