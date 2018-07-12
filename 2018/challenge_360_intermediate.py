#!/usr/bin/env python3
from opensky_api import OpenSkyApi # see https://github.com/openskynetwork/opensky-api
from math import acos, cos, inf, radians, sin, sqrt
from scipy.spatial import distance
import sys

# https://www.reddit.com/r/dailyprogrammer/comments/8i5zc3/20180509_challenge_360_intermediate_find_the/

"""
Eifel Tower:
48.8584 N
2.2945 E

John F. Kennedy Airport:
40.6413 N
73.7781 W
"""

# output format:
"""
Geodesic distance
Callsign
Latitude and Longitude (WGS-84) and degrees
Geometric Altitude (metres)
Country of origin
ICAO24 ID
"""
def get_state_details(s, distance=1):
	return """Distance: {}
Callsign: {}
Lat/Long: {}, {}
Geometric Altitude: {}
Country of Origin: {}
ICAO24 ID: {}
""".format(distance, s.callsign, s.latitude, s.longitude, s.geo_altitude, s.origin_country, s.icao24)

# Euclidean distance from a to b
# a and b should be tuples with two elements, (lat, long)
# if bonus is True, use the https://en.wikipedia.org/wiki/Great-circle_distance
def calc_distance(a, b, bonus=False):
	# missing information
	if a[0] == None or a[1] == None or b[0] == None or b[1] == None:
		return inf

	if bonus:
		# input is (lat, long)
		# convert to radians
		r_a_lat = radians(a[0])
		r_b_lat = radians(b[0])
		delta_lat = a[0] - b[0]
		delta_long = abs(a[1] - b[1])
		mean_lat = (a[0] + b[0])/2
		radius = 6371 # km

		central_angle = acos(sin(r_a_lat) * sin(r_b_lat) + cos(r_a_lat) * cos(r_b_lat) * cos(delta_long))
		return radius * central_angle
		# return radius * sqrt(delta_lat**2 + (cos(mean_lat)*delta_long)**2)
	else:
		return distance.euclidean(a, b)
		# return sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

def main():
	# automatically bonus (great-circle distance) if any argument is provided
	bonus = True if len(sys.argv) > 1 else False

	# read from the API: https://opensky-network.org/api/states/all
	api = OpenSkyApi()
	states = api.get_states()

	home_lat = float(input().split(' ')[0]) # degrees
	home_long = float(input().split(' ')[0]) # degrees

	print("Closest plane to {}, {} at {}".format(home_lat, home_long, states.time))
	print('-'*40)

	# look for the closest flight to home
	best_state = min(states.states, key=lambda x: calc_distance((home_lat, home_long), (x.latitude, x.longitude), bonus))
	print(get_state_details(best_state, calc_distance((home_lat, home_long), (best_state.latitude, best_state.longitude), bonus)))
	print("More details at https://flightaware.com/live/flight/{}".format(best_state.callsign))

if __name__ == '__main__':
	main()
