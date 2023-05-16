function set_textbox(){
    let tb = document.getElementById('set_value');
    let new_box = null;
    for(let row=1; row<11;row++){
        for(let col=1; col<7;col++){
                new_box = document.createElement('input');
                new_box.setAttribute('type','text');
                new_box.setAttribute('value','0');
                new_box.setAttribute('id','value_box_'+(col+(row-1)*6));
                new_box.setAttribute('onclick','valueBox(value_box_'+(col+(row-1)*6)+');');
                new_box.style.cssText = '\
                grid-column-start:'+((col-1)*2+1)+';\
                grid-column-end: '+((col-1)*2+2)+';\
                grid-row-start:'+((row-1)*2+1)+';\
                grid-row-end:'+((row-1)*2+1)+';\
                '
                tb.appendChild(new_box);
            if(col != 6){
                new_box = document.createElement('span');
                new_box.innerHTML= '&rarr;';
                new_box.style.cssText = '\
                grid-column-start:'+((col-1)*2+2)+';\
                grid-column-end: '+((col-1)*2+3)+';\
                grid-row-start:'+((row-1)*2+1)+';\
                grid-row-end:'+((row-1)*2+1)+';\
                '
                tb.appendChild(new_box);
            }
        }
    }

    tb = document.getElementById('set_delay');
    
    for(let row=1; row<10;row++){
        new_box = document.createElement('input');
        new_box.setAttribute('type','text');
        new_box.setAttribute('id','delay_'+row);
        new_box.setAttribute('value','100');
        new_box.setAttribute('onclick','delayBox(delay_'+row+');');
        new_box.style.cssText = '\
        grid-row-start:'+((row-1)*2+1)+';\
        grid-row-end:'+((row-1)*2+1)+';\
        margin: 0% 10% 0% 10%;\
        '
        tb.appendChild(new_box);
    }
}

function valueBox(pId){
    let value_box_ = document.getElementById("pId");
    
}

function delayBox(pId){
    let value_box_ = document.getElementById("pId");
    
}

function draw_rect(ctx, x,y,width,height, angle, color = "blue", kind="_"){

    ctx.beginPath();
    angle = 90+angle;
    //if (angle != 90){
    //let direction = angle>90 ? 180-angle : angle; 
    let z = ((height*height+width*width/4)**(1/2));
    let g = Math.atan(width/2/height)*180/Math.PI;
    let o2 = angle - g;
    let o1 = angle  + g;
    let o3 = angle - 90;
    let o4 = 90 + angle;
    o2 = o2 * Math.PI/180
    o1 = o1 * Math.PI/180
    o3 = o3 * Math.PI/180
    o4 = o4 * Math.PI/180
    let rt = [x-Math.cos(o2)*z,y-Math.sin(o2)*z];
    let lt = [x-Math.cos(o1)*z,y-Math.sin(o1)*z];
    let rb = [x-Math.cos(o3)*width/2,y-Math.sin(o3)*width/2];
    let lb = [x-Math.cos(o4)*width/2,y-Math.sin(o4)*width/2];
    ctx.beginPath();
    ctx.moveTo(rt[0], rt[1]);
    ctx.lineTo(lt[0], lt[1]);
    ctx.lineTo(lb[0], lb[1]);
    ctx.lineTo(rb[0], rb[1]);
    ctx.closePath();
    ctx.fillStyle = color; // 색상 설정
    ctx.fill(); // 내부 채우기
    ctx.stroke(); // 선 그리기

    function c(a,b){
        let z = [(a[0]+b[0])/2,(a[1]+b[1])/2];
        return z;
    }
    if(kind === "t"){
        return c(rt,lt);    
    }else if(kind === "b"){
        return c(rb,lb);
    }else{
        return (c(rt,lt),c(rb,lb));
    }
}

function syncronize_motion(ctx, save_motion){
    let servo_len = 6;
    let servo_center = 2;

    let center_t = draw_rect(ctx,250,380,20,30,save_motion[servo_center],color="black",kind="t");
    let center_b = draw_rect(ctx,250,450,50,70,0,color="#666666",kind="b");
    let t_angle = save_motion[servo_center];
    let b_angle = 0;

    for(let i=servo_center-1; i>=0; i--){
        center_t = draw_rect(ctx,center_t[0],center_t[1],50,70,t_angle,color="#666666",kind="t");
        t_angle += save_motion[i];
        center_t = draw_rect(ctx,center_t[0],center_t[1],20,30,t_angle,color="black",kind="t");
    }
    center_t = draw_rect(ctx,center_t[0],center_t[1],50,70,t_angle,color="#666666",kind="t");
    for(let i=servo_center+1;i<servo_len-1;i++){
        if (servo_center+1 ==i){
            center_b = draw_rect(ctx,center_b[0],center_b[1],20,30,180,color="black",kind="t");
        }else{
            center_b = draw_rect(ctx,center_b[0],center_b[1],20,30,180-b_angle,color="black",kind="t");
        }
        b_angle += save_motion[i];
        center_b = draw_rect(ctx,center_b[0],center_b[1],50,70,180-b_angle,color="#666666",kind="t");
    }
}

function simulator_start(pId){
    let canvas = document.getElementById('simulator');
    let ctx = canvas.getContext('2d');
    let loop = document.getElementById('loop').checked;
    let save_motion = [
        0,0,0,0,0
    ]

    if (pId === null){
        draw_rect(ctx, 250,150,50,70 , 0,color="#666666");
        draw_rect(ctx, 250,250,50,70 , 0,color="#666666");
        draw_rect(ctx, 250,350,50,70 , 0,color="#666666");
        draw_rect(ctx, 250,450,50,70 , 0,color="#666666");
        draw_rect(ctx, 250,550,50,70 , 0,color="#666666");
        draw_rect(ctx, 250,650,50,70 , 0,color="#666666");

        draw_rect(ctx, 250,180,20,30 , 0,color="#000000");
        draw_rect(ctx, 250,280 ,20,30 , 0,color="#000000");
        draw_rect(ctx, 250,380,20,30 , 0,color="#000000");
        draw_rect(ctx, 250,480,20,30 , 0,color="#000000");
        draw_rect(ctx, 250,580,20,30 , 0,color="#000000");
    }else{

        let motion,delay = 0;
        switch (pId) {
            case 1:
                motion = getMotion();
                delay = motion[1];
                motion = motion[0];
                break;
            case 2:
                motion = sin_Motion();
                delay = motion[1];
                motion = motion[0];
                break;
            case 3:
                motion = arduino();
                delay = motion[1];
                motion = motion[0];
                break;
            default:
                break;
        }
    
        let i = 0;
        let timer = setInterval(function(){
            if (motion.length <= i){
                if (loop === true){
                    i = 0;
                }else{
                    clearInterval(timer);
                    return;
                }
            }

            delay[i] -= 10;
            if(delay[i] <= 0){
                let m = motion[i];
    
                save_motion = m.slice(0,5);
                save_motion = save_motion.map(Number);
                ctx.clearRect(0, 0, 492, 692);
                syncronize_motion(ctx, save_motion);
    
                i++;
            }
        }, 10);
    }

}

function arduino(){
    let motion = [];
    let delay = [0];
    let m = []
    for(let i=0;i<314;i += 0.1){
        m=[
            Math.sin(i+0.75)*30,
            -Math.sin(i+0.5)*30,
            Math.sin(i+0.25)*30,
            -Math.sin(i) * 30,
            Math.sin(i) * 30
        ];
        motion.push(m);
        delay.push(20);
    }
    return [motion, delay];

}

function sin_Motion(){
    let motion = [];
    let delay = [0];
    let m = []
    for(let i=0;i<3600;i++){
        m=[];
        for(let j=0;j<6;j++){
            m.push(Math.sin((i+j*410)/100)*30);
        }
        motion.push(m);
        delay.push(10);
    }
    return [motion, delay];
}

function getMotion(){
    let motion = [];
    let delay = [0];
    for(let row=0; row<10;row++){
        motion.push([]);
        for(let col=0; col < 6; col++){
            let value_ = document.getElementById('value_box_'+(col+1+(row)*6));
            value_ = value_.value;
            motion[row].push(value_);
        }
        if (row != 9){
            let delay_ = document.getElementById('delay_'+(row+1));
            delay_ = delay_.value;
            delay.push(delay_);
        }
    }
    return [motion, delay];

}