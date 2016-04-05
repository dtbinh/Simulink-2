function [rK4]=dqb1(qb,dob)
rK4=(1/2)*quatmultiply(qb,[0 dob.']);