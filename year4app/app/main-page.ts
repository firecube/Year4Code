
export function loaded(args) {
    var page = args.object;
    var btnColour = page.getViewById('btnColour');
    pulse(btnColour, 0.05);
}

function pulse(control: any, diff: number) {
    var options = {
        scale: { x: 1 + diff, y: 1 + diff },
        duration: 500
    }
    
    control.animate(options).then(() => {
        options.scale = { x: 1 - diff, y: 1 - diff }
        control.animate(options).then(() => {
            pulse(control, diff);
        });
    });
}