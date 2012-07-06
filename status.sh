sed -n 'H; /^snapshot/h; ${g;p;}' snapshot | awk 'NR%100==1'
