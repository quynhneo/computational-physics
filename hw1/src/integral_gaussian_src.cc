#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <fstream>

#include "../include/integral_gaussian_include.hh"

float epsilon_m = 0.0000001; //machine precision


namespace integral
{

using namespace std;

float integral_gaussian (float x, float a, float b) //integral range a,b and initial number of interval 
{
    double relative_err;
    float output;
    
    ofstream outfile;
    outfile.open("gaussian.dat");//name of output textfile
    
    static float x11[6] = {0.0000000000000000000000000,0.2695431559523449723315320,0.5190961292068118159257257,0.7301520055740493240934163,0.8870625997680952990751578,0.9782286581460569928039380};
    static float w11[6] = {0.2729250867779006307144835,0.2628045445102466621806889,0.2331937645919904799185237,0.1862902109277342514260976,0.1255803694649046246346943,0.0556685671161736664827537};       


        output=0;  //reset the variable                  
        
       
        float sum=0;//reset the sum
         
        for (int i =0; i < 6 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                sum= sum+  w11[i] * static_cast<float>( exp(-x11[i]) ) ;
                
                
                output=sum;
              // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        cout << "right value"<<(exp(1)-1 )/exp(1)<<endl;
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << 5  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << 5 <<" "<< relative_err <<endl ;//writing out to text file     
    
    static float x19[10] = {0.0000000000000000000000000,0.1603586456402253758680961,0.3165640999636298319901173,0.4645707413759609457172671,0.6005453046616810234696382,0.7209661773352293786170959,0.8227146565371428249789225,0.9031559036148179016426609,0.9602081521348300308527788,0.9924068438435844031890177};
    static float w19[10] = {0.1610544498487836959791636,0.1589688433939543476499564,0.1527660420658596667788554,0.1426067021736066117757461,0.1287539625393362276755158,0.1115666455473339947160239,0.0914900216224499994644621,0.0690445427376412265807083,0.0448142267656996003328382,0.0194617882297264770363120};
    
    
    output=0;  //reset the variable                  
        
       
         sum=0;//reset the sum
         
        for (int i =0; i < 10 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                sum= sum+  w19[i] * static_cast<float>( exp(-x19[i]) ) ;
                
                
                output=sum;
              // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        cout << "right value"<<(exp(1)-1 )/exp(1)<<endl;
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << 9  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << 9 <<" "<< relative_err <<endl ;//writing out to text file     


static double x32[16] = {0.0483076656877383162348126,0.1444719615827964934851864,0.2392873622521370745446032,0.3318686022821276497799168,0.4213512761306353453641194,0.5068999089322293900237475,0.5877157572407623290407455,0.6630442669302152009751152,0.7321821187402896803874267,0.7944837959679424069630973,0.8493676137325699701336930,0.8963211557660521239653072,0.9349060759377396891709191,0.9647622555875064307738119,0.9856115115452683354001750,0.9972638618494815635449811};
static double w32[16] = {0.0965400885147278005667648,0.0956387200792748594190820,0.0938443990808045656391802,0.0911738786957638847128686,0.0876520930044038111427715,0.0833119242269467552221991,0.0781938957870703064717409,0.0723457941088485062253994,0.0658222227763618468376501,0.0586840934785355471452836,0.0509980592623761761961632,0.0428358980222266806568786,0.0342738629130214331026877,0.0253920653092620594557526,0.0162743947309056706051706,0.0070186100094700966004071};



output=0;  //reset the variable                  
        
       
         sum=0;//reset the sum
         
        for (int i =0; i < 16 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                sum= sum+  w32[i] * static_cast<float>( exp(-x32[i]) ) ;
                
                
                output=sum;
              // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        cout << "right value"<<(exp(1)-1 )/exp(1)<<endl;
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << 15  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << 15 <<" "<< relative_err <<endl ;//writing out to text file     

static float x64[32] = {0.0243502926634244325089558,0.0729931217877990394495429,0.1214628192961205544703765,0.1696444204239928180373136,0.2174236437400070841496487,0.2646871622087674163739642,0.3113228719902109561575127,0.3572201583376681159504426,0.4022701579639916036957668,0.4463660172534640879849477,0.4894031457070529574785263,0.5312794640198945456580139,0.5718956462026340342838781,0.6111553551723932502488530,0.6489654712546573398577612,0.6852363130542332425635584,0.7198818501716108268489402,0.7528199072605318966118638,0.7839723589433414076102205,0.8132653151227975597419233,0.8406292962525803627516915,0.8659993981540928197607834,0.8893154459951141058534040,0.9105221370785028057563807,0.9295691721319395758214902,0.9464113748584028160624815,0.9610087996520537189186141,0.9733268277899109637418535,0.9833362538846259569312993,0.9910133714767443207393824,0.9963401167719552793469245,0.9993050417357721394569056};
static float w64[32] = {0.0486909570091397203833654,0.0485754674415034269347991,0.0483447622348029571697695,0.0479993885964583077281262,0.0475401657148303086622822,0.0469681828162100173253263,0.0462847965813144172959532,0.0454916279274181444797710,0.0445905581637565630601347,0.0435837245293234533768279,0.0424735151236535890073398,0.0412625632426235286101563,0.0399537411327203413866569,0.0385501531786156291289625,0.0370551285402400460404151,0.0354722132568823838106931,0.0338051618371416093915655,0.0320579283548515535854675,0.0302346570724024788679741,0.0283396726142594832275113,0.0263774697150546586716918,0.0243527025687108733381776,0.0222701738083832541592983,0.0201348231535302093723403,0.0179517157756973430850453,0.0157260304760247193219660,0.0134630478967186425980608,0.0111681394601311288185905,0.0088467598263639477230309,0.0065044579689783628561174,0.0041470332605624676352875,0.0017832807216964329472961};

output=0;  //reset the variable                  
        
       
         sum=0;//reset the sum
         
        for (int i =0; i < 32 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                sum= sum+  w64[i] * static_cast<float>( exp(-x64[i]) ) ;
                
                
                output=sum;
              // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        cout << "right value"<<(exp(1)-1 )/exp(1)<<endl;
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << 31  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << 31 <<" "<< relative_err <<endl ;//writing out to text file  


static float x128[64] = {0.0122236989606157641980521,0.0366637909687334933302153,0.0610819696041395681037870,0.0854636405045154986364980,0.1097942311276437466729747,0.1340591994611877851175753,0.1582440427142249339974755,0.1823343059853371824103826,0.2063155909020792171540580,0.2301735642266599864109866,0.2538939664226943208556180,0.2774626201779044028062316,0.3008654388776772026671541,0.3240884350244133751832523,0.3471177285976355084261628,0.3699395553498590266165917,0.3925402750332674427356482,0.4149063795522750154922739,0.4370245010371041629370429,0.4588814198335521954490891,0.4804640724041720258582757,0.5017595591361444642896063,0.5227551520511754784539479,0.5434383024128103634441936,0.5637966482266180839144308,0.5838180216287630895500389,0.6034904561585486242035732,0.6228021939105849107615396,0.6417416925623075571535249,0.6602976322726460521059468,0.6784589224477192593677557,0.6962147083695143323850866,0.7135543776835874133438599,0.7304675667419088064717369,0.7469441667970619811698824,0.7629743300440947227797691,0.7785484755064119668504941,0.7936572947621932902433329,0.8082917575079136601196422,0.8224431169556438424645942,0.8361029150609068471168753,0.8492629875779689691636001,0.8619154689395484605906323,0.8740527969580317986954180,0.8856677173453972174082924,0.8967532880491581843864474,0.9073028834017568139214859,0.9173101980809605370364836,0.9267692508789478433346245,0.9356743882779163757831268,0.9440202878302201821211114,0.9518019613412643862177963,0.9590147578536999280989185,0.9656543664319652686458290,0.9717168187471365809043384,0.9771984914639073871653744,0.9820961084357185360247656,0.9864067427245862088712355,0.9901278184917343833379303,0.9932571129002129353034372,0.9957927585349811868641612,0.9977332486255140198821574,0.9990774599773758950119878,0.9998248879471319144736081};
static float w128[64] = {0.0244461801962625182113259,0.0244315690978500450548486,0.0244023556338495820932980,0.0243585572646906258532685,0.0243002001679718653234426,0.0242273192228152481200933,0.0241399579890192849977167,0.0240381686810240526375873,0.0239220121367034556724504,0.0237915577810034006387807,0.0236468835844476151436514,0.0234880760165359131530253,0.0233152299940627601224157,0.0231284488243870278792979,0.0229278441436868469204110,0.0227135358502364613097126,0.0224856520327449668718246,0.0222443288937997651046291,0.0219897106684604914341221,0.0217219495380520753752610,0.0214412055392084601371119,0.0211476464682213485370195,0.0208414477807511491135839,0.0205227924869600694322850,0.0201918710421300411806732,0.0198488812328308622199444,0.0194940280587066028230219,0.0191275236099509454865185,0.0187495869405447086509195,0.0183604439373313432212893,0.0179603271850086859401969,0.0175494758271177046487069,0.0171281354231113768306810,0.0166965578015892045890915,0.0162550009097851870516575,0.0158037286593993468589656,0.0153430107688651440859909,0.0148731226021473142523855,0.0143943450041668461768239,0.0139069641329519852442880,0.0134112712886163323144890,0.0129075627392673472204428,0.0123961395439509229688217,0.0118773073727402795758911,0.0113513763240804166932817,0.0108186607395030762476596,0.0102794790158321571332153,0.0097341534150068058635483,0.0091830098716608743344787,0.0086263777986167497049788,0.0080645898904860579729286,0.0074979819256347286876720,0.0069268925668988135634267,0.0063516631617071887872143,0.0057726375428656985893346,0.0051901618326763302050708,0.0046045842567029551182905,0.0040162549837386423131943,0.0034255260409102157743378,0.0028327514714579910952857,0.0022382884309626187436221,0.0016425030186690295387909,0.0010458126793403487793129,0.0004493809602920903763943};

output=0;  //reset the variable                  
        
       
         sum=0;//reset the sum
         
        for (int i =0; i < 64 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                sum= sum+  w128[i] * static_cast<float>( exp(-x128[i]) ) ;
                
                
                output=sum;
              // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        cout << "right value"<<(exp(1)-1 )/exp(1)<<endl;
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << 63  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << 63 <<" "<< relative_err <<endl ;//writing out to text file  



}//integral


}//namespace