//
// Created by fynn on 4/10/23.
//

export module testModule;


export auto plus(auto x, auto y) -> decltype(x+y){
    return x+y;
}

