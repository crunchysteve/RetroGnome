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
    }
    for(y=[33:10:63]){
        translate([9.5,y]) difference(){
            circle(4);
            circle(3);
        }
    }

    translate([14.5,31]) text(text="GND",size=4);
    translate([14.5,41]) text(text="VCC",size=4);
    translate([14.5,51]) text(text="DIO",size=4);
    translate([14.5,61]) text(text="CLK",size=4);
}