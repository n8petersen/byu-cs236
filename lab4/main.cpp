#include <iostream>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
using namespace std;

// int main() { // Part 1

//     Scheme scheme1( { "A", "B" } );
//     Scheme scheme2( { "B", "C" } );

//     Tuple tuple1( {"'1'", "'2'"} );
//     Tuple tuple2( {"'3'", "'4'"} );

//     // cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl;

//     Scheme scheme3( { "X", "Y" } );
//     Scheme scheme4( { "X", "Y", "Z" } );

//     Tuple tuple3( {"'1'", "'4'"} );
//     Tuple tuple4( {"'1'", "'2'", "'4'"} );

//     cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl << endl;
//     // A:1  B:2  // B:3  C:4 // not joinable // 0

//     cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl << endl;
//     // B:1  C:4 // X:3  Y:4 // joinable // 1

//     cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl << endl;
//     // X:1  Y:2  // X:1  Y:2  Z:4 // joinable // 1

//     cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl << endl;
//     // X:1  Y:4  // X:1  Y:2  Z:4   // not joinable // 0


// }

int main() { // Part 2

    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
    vector<string> studentValues[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
    };
    for (auto& value : studentValues) { 
        studentRelation.addTuple(Tuple(value)); 
    }

    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
    vector<string> courseValues[] = {
        {"'42'", "'CS 100'"},
        {"'32'", "'CS 232'"},
    };
    for (auto& value : courseValues) {
        courseRelation.addTuple(Tuple(value));
    }
    
    
    studentRelation.join(courseRelation);

}