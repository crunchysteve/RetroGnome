scale([40/200,20/100]){
    difference(){
        translate([-1,-1]) offset(1) offset(-1) square([202,101.75]);
        import("/Users/steve/Downloads/trace.svg");
        translate([49.25,0]) circle(6);
        translate([-0.5,49.5]) circle(3);
        hull(){
            translate([49.25,99]) circle(6);
            translate([49.25,101]) circle(6);
        }
        translate([149.25,0]) circle(3);
        hull(){
            translate([149.25,99]) circle(3);
            translate([149.25,101]) circle(3);
        }
        translate([200,49.5]) circle(6);
        translate([5,30]) square([20,40]);
        translate([65,7]) square([70,15]);
    }
    for(y=[33:10:63]){
        translate([9.5,y]) difference(){
            circle(4);
            circle(3);
        }
    }
}
