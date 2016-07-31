# Pedin  
Indoor pedestrian simulator based on the social force model.  
##Instructions:  
- Clone the repo  
- Change folder to pedin  
- Run make  
- Start simulator by running startSim.sh  

##Maps Documentation:
        - Please refer to the sample maps in the maps folder.
        - Every line in the map file(.mpf) corresponds to a wall,(a polygon may be used to make an obstacle)
        - Every wall has a midpoint coordinates x,y (in cm) ,a normal vector to represent direction of repulsion, and length(in cm)
