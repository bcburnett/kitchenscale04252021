module.exports = class Recipe {
    title = '';
    levels={
        EASY:'EASY',
        MODERATE: 'MODERATE',
        HARD:'HARD',
        EXPERT:'EXPERT'
    };
    level=levels.EASY;
    ingredients = [];
    cuisine='';
    comments=[];
    dishes={
        BREAKFAST:'BREAKFAST',
        LUNCH:'LUNCH',
        DINNER:'DINNER',
        DESERT:'DESERT',
        MAIN_COURSE:'MAIN_COURSE',
        SIDE:'SIDE',
        BRUNCH:'BRUNCH',
    };
    dishtype='';
    image='';
    url='';
    duration=0;
    creator='';
    created= new Date();

    setLevel(mylevel){
        if(!(mylevel in this.levels)) return {success:false,error:'level must be a part of recipe.levels'};
        this.level = mylevel;
        return {success:true, res:mylevel}
    }

    setDishType(mydish){
        if(!(mydish in this.dishes)) return {success:false,error:'dish must be a part of recipe.dishes'};
        this.dishtype = mydish;
        return {success:true, res:mydish}
    }

    createIngredient(myName, myAmmount, myMeasure){
        if(typeof(myName)!=='string'||myName=='') return {success:false,error:'name must be a string'}
        if(typeof(myMeasure)!=='string'||myMeasure=='') return {success:false,error:'measure must be a string'}
        if(typeof(myAmmount)!=='number'||myAmmount==0)return {success:false,error:'measure must be a number'}
        const ingredient = new Ingredient(myAmmount, myMeasure, myName)
        this.ingredients = [...this.ingredients,ingredient.getIngredient()];
        return {success:true, res:ingredient}
    }



}

class Ingredient {
    name='';
    ammount=0;
    measure='';
    constructor(amount, measure, name){
        this.amount = amount;
        this.measure = measure;
        this.name = name;
    }

    getIngredient(){
        return {
            name: this.name,
            ammount: this.ammount,
            measure: this.measure,
        }
    }
}