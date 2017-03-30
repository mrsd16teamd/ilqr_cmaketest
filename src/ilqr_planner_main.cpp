#include <vector>
#include <iostream>

extern "C"{
  #include "iLQG_mpc.c"
}

// #include "iLQR_mpc.c" //TODO integrate generated c-code
//iLQR_mpc(double x_cur[10], double x_des[6], double obs[2], int T);

// Note that the inputs to this function can be whatever is convenient for client
// ilqr_loco::TrajExecGoal iLQR_gen_traj(nav_msgs::Odometry x_cur, std::vector<double> x_des,
//                                         std_msgs::Float32MultiArray obstacle_pos, int T)
int main()
{
  double x0[10] = {1, 1, 0,  1, 0, 0,  1, 0, 0, 0};
  double xDes[6] = {4, 0, 0,  0, 0, 0};
  double Obs[2] = {2.5, 0};

  int T = 30;
  int N = T+1;
  int n = 10;
  int m = 2;

  struct trajectory Traj;
  Traj.x = (double *) malloc(n*N*sizeof(double));
  Traj.u = (double *) malloc(m*(N-1)*sizeof(double));

  // traj[0]: states, traj[1]: controls
  plan_trajectory(x0,xDes,Obs,T,&Traj);

  for(int i=0; i<N; i++) {
    std::cout << "state: " << Traj.x[i*n+0] << " " <<  Traj.x[i*n+1] <<
    Traj.x[i*n+3] << " " <<  Traj.x[i*n+4] << " " << Traj.x[i*n+5] <<  '\n';
  }

  for(int i=0; i<N-1; i++) {
    std::cout << "Output: " << Traj.u[i*m+0] << " " << Traj.u[i*m+1] << '\n';
  }

  return 0;
}
