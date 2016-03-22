import {Observable} from 'data/observable';

export class Colour extends Observable {
    
    constructor() {
        super();
        this._r = this._g = this._b = 255;
        this.rgb = this.rgbToHex(this._r, this._g, this._b);
    }
    
    private _r: number;
    private _g: number;
    private _b: number;
    
    rgb: string;

    get r(): number {
        return this._r;
    }
    set r(value: number) {
        if (this._r !== value) {
            this._r = value;
            this.rgb = this.rgbToHex(this._r, this._g, this._b);
            this.notifyPropertyChange("r", value);
            this.notifyPropertyChange("rgb", this.rgb);
        }
    }
    
    get g(): number {
        return this._g;
    }
    set g(value: number) {
        if (this._g !== value) {
            this._g = value;
            this.rgb = this.rgbToHex(this._r, this._g, this._b);
            this.notifyPropertyChange("g", value);
            this.notifyPropertyChange("rgb", this.rgb);
        }
    }
    
    get b(): number {
        return this._b;
    }
    set b(value: number) {
        if (this._b !== value) {
            this._b = value;
            this.rgb = this.rgbToHex(this._r, this._g, this._b);
            this.notifyPropertyChange("b", value);
            this.notifyPropertyChange("rgb", this.rgb);
        }
    }
    
    componentToHex(c) {
        var hex = c.toString(16);
        return hex.length == 1 ? "0" + hex : hex;
    }

    rgbToHex(r, g, b) {
        return "#" + this.componentToHex(r) + this.componentToHex(g) + this.componentToHex(b);
    }
    
}

export default new Colour();