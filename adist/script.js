var canvas = document.getElementById('canvas');
var context = canvas.getContext('2d');

var blocks = [
    { x: 3, y: 0 },
    { x: 4, y: 0 },
    { x: 3, y: 1 },
    { x: 4, y: 1 },
    { x: 0, y: 2 },
    { x: 1, y: 2 },
    { x: 2, y: 2 },
    { x: 3, y: 2 },
    { x: 4, y: 2 },
    { x: 5, y: 2 },
    { x: 6, y: 2 },
    { x: 7, y: 2 },
    { x: 0, y: 3 },
    { x: 1, y: 3 },
    { x: 2, y: 3 },
    { x: 3, y: 3 },
    { x: 4, y: 3 },
    { x: 5, y: 3 },
    { x: 6, y: 3 },
    { x: 7, y: 3 },
];

var offset = 100
var blockSize = 50;
var directions = 8;

var numAgents = Math.round(blocks.length / 3);

var agents = [];
for(var i = 0; i < numAgents; i++) {
    var halfBlockSize = Math.floor(blockSize / 2);
    agents.push({
//        x: offset + blockSize * blocks[0].x + halfBlockSize,
//        y: offset + blockSize * blocks[0].y + halfBlockSize,
        x: offset + blockSize * blocks[0].x + Math.floor(Math.random() * 50),
        y: offset + blockSize * blocks[0].y + Math.floor(Math.random() * 50),
        r: blockSize + 10
    });
}

for(var i = 0; i < 1; i++) {
    var heatMaxPoint = calculateHeatMaxPoint();

    var closestAgent = 0;
    var dX = Math.abs(agents[0].x - heatMaxPoint.x);
    var dY = Math.abs(agents[0].y - heatMaxPoint.y);
    var dClosest2 =  dX * dX + dY * dY;
    for(var j = 1; j < agents.length; j++) {
        var dX = Math.abs(agents[j].x - heatMaxPoint.x);
        var dY = Math.abs(agents[j].y - heatMaxPoint.y);
        var d2 = dX * dX + dY * dY;
        if(d2 < dClosest2) {
            closestAgent = j;
            dClosest2 = d2;
        }
    }
    //calculateBlockOverlap();
}

for(var i = 0; i < blocks.length; i++) {
    context.fillStyle = Math.floor(Math.random() * 2) % 2 ? 'rgb(0, 0, 200)' : 'rgb(50, 50, 200)';
    context.fillRect(offset + blockSize * blocks[i].x, offset + blockSize * blocks[i].y, blockSize, blockSize);
}

for(var i = 0; i < agents.length; i++) {
    context.fillStyle = 'rgba(200, 0, 200, 0.5)';
    context.beginPath();
    context.arc(agents[i].x, agents[i].y, agents[i].r, 0, 2 * Math.PI, true);
    context.fill();
}


function calculateBlockOverlap(agent) {
    var xMax = 0;
    var yMax = 0;
    for(var i = 0; i < blocks.length; i++) {
        if(blocks[i].x > xMax) {
            xMax = blocks[i].x;
        }
        if(blocks[i].y > yMax) {
            yMax = blocks[i].y;
        }
    }

    var overlaps = 0;
    for(var y = offset; y < offset + blockSize * (yMax + 1); y++) {
        for(var x = offset; x < offset + blockSize * (xMax + 1); x++) {
            for(var i = 0; i < blocks.length; i++) {
                if(x >= offset + blockSize * blocks[i].x
                && x < offset + blockSize * (blocks[i].x + 1)
                && y >= offset + blockSize * blocks[i].y
                && y < offset + blockSize * (blocks[i].y + 1)) {
                    var r2 = agent.r * agent.r;
                    var dX = Math.abs(agent.x - x);
                    var dY = Math.abs(agent.y - y);
                    if(dX * dX + dY * dY <= r2) {
                        overlaps++;
                    }
                }
            }
        }
    }
    return overlaps;
}

function calculateAgentOverlap(agent) {
}

function calculateHeatMaxPoint() {
    var xMax = 0;
    var yMax = 0;
    for(var i = 0; i < blocks.length; i++) {
        if(blocks[i].x > xMax) {
            xMax = blocks[i].x;
        }
        if(blocks[i].y > yMax) {
            yMax = blocks[i].y;
        }
    }

    var heatMap = [];
    for(var y = 0; y < blockSize * (yMax + 1); y++) {
        var row = []
        for(var x = 0; x < blockSize * (xMax + 1); x++) {
            row.push(0);
        }
        heatMap.push(row);
    }

    var heatMax = 0;
    var heatMaxPoints = []; 
    for(var y = offset; y < offset + blockSize * (yMax + 1); y++) {
        for(var x = offset; x < offset + blockSize * (xMax + 1); x++) {
            for(var j = 0; j < agents.length; j++) {
                var r2 = agents[j].r * agents[j].r;
                var dX = Math.abs(agents[j].x - x);
                var dY = Math.abs(agents[j].y - y);
                if(dX * dX + dY * dY <= r2) {
                    heatMap[y - offset][x - offset]++;
                    if(heatMap[y - offset][x - offset] >= heatMax) {
                        heatMax = heatMap[y - offset][x - offset];
                        heatMaxPoints.push({ x: x, y: y, value: heatMap[y - offset][x - offset] });
                    }
                }
            }
        }
    }

    while(heatMaxPoints[0].value < heatMax) {
        heatMaxPoints.shift();
    }

    return heatMaxPoints[Math.floor(Math.random() * heatMaxPoints.length)];
}

