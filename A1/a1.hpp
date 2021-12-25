/*  Viswa Nihar
 *  Nukala
 *  viswanih
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
    int size, rank;

    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    std::vector<int> send_num_of_elements(size, 0);
    std::vector<int> send_num_of_elements_1(size, 0);

    // Start iterating over the vector and fill the num_of_elements arrays depending on the destination it needs to go to.
    for(int i=0; i<Xi.size(); i++) {
        int destination = (Xi[i] + size) / 2;
        if(destination == 0) {
            send_num_of_elements_1[destination]++;
        } else if(destination != 0) {
            int element_diff = (Xi[i] + size) % 2;
            if(element_diff == 0) {
                send_num_of_elements[destination]++;
            } else if(element_diff == 1) {
                send_num_of_elements_1[destination]++;
            }
        }
    }

    // Start sending the counts of each element to the respective processor.
    for(int i=0; i<size; i++) {
        MPI_Send(&send_num_of_elements[i] , 1 , MPI_INT , i , 222 , comm);
        MPI_Send(&send_num_of_elements_1[i] , 1 , MPI_INT , i , 111 , comm);
    }

    Xi.clear();

    int recv;
    int elem;

    // Start receiving elements of tag 222 and add them to Xi.
    for(int i=0; i<size; i++) {
        MPI_Recv( &recv , 1 , MPI_INT , MPI_ANY_SOURCE , 222 , comm , MPI_STATUS_IGNORE);
        // Create the element from the message tag and add the elements to the original vector.
        elem = ((2 * rank) - size) + 0;
        for(int j=0; j<recv; j++) {
            Xi.push_back(elem);
        }
    }

    // Start receiving elements of tag 111 and add them to Xi.
    for(int i=0; i<size; i++) {
        MPI_Recv( &recv , 1 , MPI_INT , MPI_ANY_SOURCE , 111 , comm , MPI_STATUS_IGNORE);
        elem = ((2 * rank) - size) + 1;
        for(int j=0; j<recv; j++) {
            Xi.push_back(elem);
        }
    }

    // To view uncomment the following lines.
    //MPI_Barrier(comm);

    /*for(int i=0; i<size; i++) {
        if(rank == i) {
            std::cout << rank << ": ";
            for(int j=0; j<Xi.size(); j++) {
                std::cout << Xi[j] << " ";
            }
            std::cout << "\n";
        }
    }*/
    
} // isort

#endif // A1_HPP