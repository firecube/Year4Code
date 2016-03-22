import {Page} from 'ui/page';
import {EventData} from "data/observable";
import * as http from 'http';
import {default as selectedColour} from './colour'

export function loaded(args: EventData) {
    var page = <Page>args.object;
    page.bindingContext = selectedColour;
    
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

export function colourPicker(args: EventData) {
    let page:Page = (<any>args.object).page;
    
    var modal = './colour-picker';
    var context = 'some custom context';
    var fullscreen = true;
    page.showModal(modal, context, function closeCallback () {
        let url = `http://192.168.2.1/setcolour?r=${selectedColour.r}&g=${selectedColour.g}&b=${selectedColour.b}`;
        http.getString(url);
    }, fullscreen);
}