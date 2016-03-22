import {Page} from 'ui/page';
import {ShownModallyData} from 'ui/page';
import {default as selectedColour} from './colour'

var context: any;
var closeCallback: Function;

export function onShownModally(args: ShownModallyData) {
    context = args.context;
    closeCallback = args.closeCallback;
    
    var page = <Page>args.object;
    page.bindingContext = selectedColour;
}

export function onChooseColour() {
    closeCallback();
}