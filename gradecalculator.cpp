#include "gradecalculator.h"

#include <algorithm>
#include <iterator>

void GradeCalculator::Load(std::istream& is)
{             
	// TODO Load the grades 

	if(m_Grades.empty()) { // NOTE ensure the grades vector only contains the newly loaded grades	
		Type type;
       		double score;   
		
		is >> type >> score; // obtain first line from file

		while(!is.eof()) {	 
       			if(type == QUIZ || type == ASSIGNMENT || type == TEST || type == EXAM) {
                        	      m_Grades[type].push_back(score); // insert score into vector corresponding with key value (grade type)
			}
			
			is >> type >> score; // continue reading lines until we raech the e.o.f.
		}
	} else {
		std::cerr << "There is data currently being stored in m_Grades. Would you like to clear m_Grades and upload new data?"
                          << "Press (1) to upload new data, (0) to terminate."; //ask user if they want to clear m_Grades & continue with program

                bool choice;
                std::cin >> choice;

                if(choice) {
                        m_Grades.clear(); //if true (user selects 1), clear data currently stored in m_Grades
                        Load(is); // call load function to load new grades
                }
                else {
                        abort(); //abort function if user wants to keep data in m_Grades
                }		
	} 	
}
	
CountAverage GradeCalculator::CalculateAverage(Type type) const
{
	// TODO Calculate the count and average for the provided type without writing a loop

        CountAverage pair; // declare variable to store <count, average> for the requested GradeCalculator::Type

	std::map<Type, std::vector<double> >::const_iterator it = m_Grades.find(type); // find requested key (grade type) in map 
	std::vector<double> scores;
	
	copy(it->second.begin(), it->second.end(), back_inserter(scores)); // copy values (grade scores) from previously found vector in map, into vector 'scores' for easier access       

	pair.second = accumulate(scores.begin(), scores.end(), 0); // accumulate sum of grade scores in vector of requested type
	pair.first = scores.size(); // obtain number of scores in vector of requested type

        if(pair.first != 0) { // account for division by zero
		pair.second =  pair.second / pair.first; //divide the total sum of scores for that grade type by its count
        	return pair; //return <count, average>
	}
	else { // if no grades recorded for type, return zero for both average and count
		pair.second = 0.0;
		pair.first = 0;
		return pair;
	}
}
