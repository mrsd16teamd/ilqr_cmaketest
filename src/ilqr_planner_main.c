#include <math.h>
#include "iLQG_mpc.h"

// #include "iLQR_mpc.c" //TODO integrate generated c-code
//iLQR_mpc(double x_cur[10], double x_des[6], double obs[2], int T);

// Note that the inputs to this function can be whatever is convenient for client
int main()
{
  // TODO pre-process inputs as necessary, put into C-style arrays

  // TODO convert orientation from quaternion
  int T = 50;
  double x0[10] = {0,0,0, 3,0,0,3,0,0,0};
  double xDes[6] = {3.0, 3.0, 1.5, 3.0, 0.0, 0.0};
  double Obs[2] = {1.0, 0.0};
  
  // double theta = tf::getYaw(x_cur.pose.pose.orientation);

  // double x0[10] = {x_cur.pose.pose.position.x, x_cur.pose.pose.position.y, theta,
  //                         x_cur.twist.twist.linear.x, x_cur.twist.twist.linear.y,
  //                         x_cur.twist.twist.angular.z,
  //                         x_cur.twist.twist.linear.x, 0, 0, 0}

  // double* xDes = &x_des[0];
  // double* Obs = {(double)obstacle_pos.data[0],(double)obstacle_pos.data[1]};

  // TODO what is the output type?
  int N = T+1;
  int n = 10;
  int m = 2;

  struct trajectory Traj;
  Traj.x = (double *)malloc(n*N*sizeof(double));
  Traj.u = (double *)malloc(m*(N-1)*sizeof(double));
  // traj[0]: states, traj[1]: controls
  plan_trajectory(x0,xDes,Obs,T,&Traj);



 // ilqr_loco::TrajExecGoal goal;
 // TODO put output from c-code into action message

 //  for(int i=0; i<N; i++) {
 //   	nav_msgs::Odometry odom;

 //    odom.pose.pose.position.x = Traj.x[i*n+0]; // x
 //    odom.pose.pose.position.y = Traj.x[i*n+1]; // y
 //    odom.pose.pose.position.z = 0.0;

 //    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(Traj.x[i*n+2]); // phi
 //    odom.twist.twist.linear.x = Traj.x[i*n+3]; // Ux
 // 	odom.twist.twist.linear.x = Traj.x[i*n+4]; // Uy
 // 	odom.twist.twist.angular.z = Traj.x[i*n+5]]; // r

	// goal.traj.states.push_back(odom);
 //  }

 //  for(int i=0; i<N-1; i++) {
 //  	geometry_msgs::Twist twist;
 //  	twist.linear.x = Traj.u[i*m+0];
 //  	twist.angular.z = Traj.u[i*m+1];
 //  	goal.traj.states.push_back(twist);
 //  }
  int i, j;
  FILE *fp = fopen("X.csv", "w");
  for(i=0; i<N; i++) {
    for(j=0; j<n; j++) {
        fprintf(fp, "%f, ", Traj.x[i*n+j]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  fp = fopen("U.csv", "w");
  for(i=0; i<N-1; i++) {
    fprintf(fp, "%f, %f\n", Traj.u[i*m], Traj.u[i*m+1]);
  }
  fclose(fp);

 //  return goal;
  return 1;
}