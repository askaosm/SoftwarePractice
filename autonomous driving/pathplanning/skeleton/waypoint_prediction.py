import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
from scipy.interpolate import splprep, splev
from scipy.optimize import minimize
import time
import sys


def normalize(v):
    norm = np.linalg.norm(v,axis=0) + 0.00001
    return v / norm.reshape(1, v.shape[1])



def curvature(waypoints):
    '''
    ##### TODO #####
    Curvature as  the sum of the normalized dot product between the way elements
    Implement second term of the smoothin objective.

    args: 
        waypoints [2, num_waypoints] !!!!!
    '''

    if waypoints.shape[1] < 3:
        return 0

    #initilize
    curvature_sum = 0.0

    # calculate cureve
    for i in range(1, waypoints.shape[1]-1):
        vec1 = waypoints[:, i] - waypoints[:, i-1]
        vec2 = waypoints[:, i+1] - waypoints[:, i]
        
        
        vec1_normalized = normalize(vec1.reshape(2, 1))
        vec2_normalized = normalize(vec2.reshape(2, 1))
        
        
        curvature_sum += np.dot(vec1_normalized.T, vec2_normalized)

    curvature = curvature_sum / (waypoints.shape[1] - 2)
    return curvature


def smoothing_objective(waypoints, waypoints_center, weight_curvature=40):
    '''
    Objective for path smoothing

    args:
        waypoints [2 * num_waypoints] !!!!!
        waypoints_center [2 * num_waypoints] !!!!!
        weight_curvature (default=40)
    '''
    # mean least square error between waypoint and way point center
    ls_tocenter = np.mean((waypoints_center - waypoints)**2)

    # derive curvature
    curv = curvature(waypoints.reshape(2,-1))

    return -1 * weight_curvature * curv + ls_tocenter


def waypoint_prediction(roadside1_spline, roadside2_spline, num_waypoints=6, way_type = "smooth"):
    '''
    ##### TODO #####
    Predict waypoint via two different methods:
    - center
    - smooth 

    args:
        roadside1_spline
        roadside2_spline
        num_waypoints (default=6)
        parameter_bound_waypoints (default=1)
        waytype (default="smoothed")
    '''
    t = np.linspace(0, 1, num_waypoints)

    if way_type == "center":
        ##### TODO #####
        
        roadside1_points = np.array(splev(t, roadside1_spline))
        roadside2_points = np.array(splev(t, roadside2_spline))

        # Derive center between corresponding roadside points
        way_points = (roadside1_points + roadside2_points) / 2
        return way_points
    
    elif way_type == "smooth":
        ##### TODO #####

        roadside1_points = np.array(splev(t, roadside1_spline))
        roadside2_points = np.array(splev(t, roadside2_spline))
        initial_way_points = (roadside1_points + roadside2_points) / 2
       # optimized_waypoints = optimize_waypoints(initial_way_points, roadside1_spline, roadside2_spline, t)
        def objective(waypoints_flat):
            waypoints = waypoints_flat.reshape(2, -1)

            roadside1_points = np.array(splev(t, roadside1_spline))
            roadside2_points = np.array(splev(t, roadside2_spline))

            # 2D
            distance_to_roadside1 = np.linalg.norm(waypoints - roadside1_points, axis=0)
            distance_to_roadside2 = np.linalg.norm(waypoints - roadside2_points, axis=0)
            return np.sum(distance_to_roadside1 + distance_to_roadside2)
        
        result = minimize(objective, initial_way_points.flatten(), method='L-BFGS-B')
        return result.x.reshape(2, -1)
               
        #return way_points.reshape(2,-1)




# def target_speed_prediction(waypoints, num_waypoints_used=5,
#                             max_speed=60, exp_constant=4.5, offset_speed=30):
#def target_speed_prediction(waypoints, num_waypoints_used=5, max_speed=60, exp_constant=4.5, offset_speed=30):
def target_speed_prediction(waypoints, num_waypoints_used=5, max_speed=50, exp_constant=6.0, offset_speed=30):
  
    '''
    ##### TODO #####
    Predict target speed given waypoints
    Implement the function using curvature()

    args:
        waypoints [2,num_waypoints]
        num_waypoints_used (default=5)
        max_speed (default=60)
        exp_constant (default=4.5)
        offset_speed (default=30)
    
    output:
        target_speed (float)
    '''

    selected_waypoints = waypoints[:, :num_waypoints_used]

    # Initialize 
    curvature_sum = 0.0

    # Calculate the curvature sum
    for i in range(1, num_waypoints_used-1):
        vec1 = selected_waypoints[:, i] - selected_waypoints[:, i-1]
        vec2 = selected_waypoints[:, i+1] - selected_waypoints[:, i]

        dot_product = np.dot(vec1, vec2)
        norm_product = np.linalg.norm(vec1) * np.linalg.norm(vec2) + 0.00001

        curvature_sum += dot_product / norm_product
    #target_speed = (max_speed - offset_speed) * np.exp(-exp_constant * (num_waypoints_used -  curvature_sum)) + offset_speed
    target_speed = (max_speed - offset_speed) * np.exp(-exp_constant * (num_waypoints_used - 2 - curvature_sum)) + offset_speed
    
    return target_speed





   