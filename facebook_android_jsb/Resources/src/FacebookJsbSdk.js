/**
 * Created with JetBrains WebStorm.
 * User: LinWenhai
 * Date: 13-8-5
 * Time: 上午11:31
 * To change this template use File | Settings | File Templates.
 */

var FB = FB || {};
var Facebook = Facebook || {};

FB.cbArray = [];

FB.login = function(cb,opts){
    var argNum = arguments.length;

    if(argNum > 0){
        var type_cb = typeof cb;

        if(type_cb != 'function')
            throw "Expression is of type " +type_cb+ ",not function";

        var cbIndex = this.cbArray.indexOf(cb);
        if(cbIndex == -1)
            cbIndex = this.cbArray.push(cb) - 1;

        if(argNum == 2){
            if(opts.scope != undefined)
                Facebook.login(cbIndex,opts.scope);
            else
                Facebook.login(cbIndex);
        }
        else
            Facebook.login(cbIndex);
    }
    else
        Facebook.login(-1);
};

FB.getLoginStatus = function(cb,force){
    var argNum = arguments.length;
    if(argNum > 0){
        var type_cb = typeof cb;
        if(type_cb != 'function')
            throw "Expression is of type " +type_cb+ ",not function";

        var cbIndex = this.cbArray.indexOf(cb);
        if(cbIndex == -1)
            cbIndex = this.cbArray.push(cb) - 1;

        cc.log("getLoginStatus:"+cbIndex);
        if(argNum == 2)
            Facebook.getLoginStatus(cbIndex,force);
        else
            Facebook.getLoginStatus(cbIndex,false);
    }
};

FB.logout = function(cb){
    var argNum = arguments.length;
    if(argNum > 0){
        var type_cb = typeof cb;
        if(type_cb != 'function')
            throw "Expression is of type " +type_cb+ ",not function";

        var cbIndex = this.cbArray.indexOf(cb);
        if(cbIndex == -1)
            cbIndex = this.cbArray.push(cb) - 1;
        Facebook.logout(cbIndex);
    }
    else
        Facebook.logout(-1);
};

//path,method,params,cb
FB.api = function(par1,par2,par3,par4){
    var argNum = arguments.length;
    var error = null;

    switch(argNum){
        case 2:{
            var cbIndex = this.cbArray.indexOf(par2);
            if(cbIndex == -1)
                cbIndex = this.cbArray.push(par2) - 1;
            cc.log("path:"+par1);
            error = Facebook.api(par1,cbIndex);
            break;
        }
        case 3:{
            var cbIndex = this.cbArray.indexOf(par3);
            if(cbIndex == -1)
                cbIndex = this.cbArray.push(par3) - 1;
            error = Facebook.api(par1,JSON.stringify(par2),cbIndex);
            break;
        }
        case 4:{
            var cbIndex = this.cbArray.indexOf(par4);
            if(cbIndex == -1)
                cbIndex = this.cbArray.push(par4) - 1;
            error = Facebook.api(par1,par2,JSON.stringify(par3),cbIndex);
            break;
        }
    }
    if(error != null){
       var errorObj = eval('('+error+')');
       throw  errorObj;
    }
};

FB.ui = function(params,cb){
    var argNum = arguments.length;
    if(argNum == 2){
        var cbIndex = this.cbArray.indexOf(cb);
        if(cbIndex == -1)
            cbIndex = this.cbArray.push(cb) - 1;
        Facebook.ui(JSON.stringify(params),cbIndex);
    }
};

FB.callback = function(index,params){
    var argNum = arguments.length;
    if(argNum == 2){
        var response = eval('('+params+')');
        this.cbArray[index](response);
    }
    else
        this.cbArray[index]();
} ;