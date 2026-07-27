"""
spotify_api.py
==========
Connects to spotify to pull data.
"""
# Adding dependencies
import spotipy
from spotipy.oauth2 import SpotifyOAuth
from dotenv import load_dotenv
import os

load_dotenv()

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=os.getenv("CLIENT_ID"),
    client_secret=os.getenv("CLIENT_SECRET"),
    redirect_uri="http://127.0.0.1:8888/callback",
    scope="user-read-currently-playing user-read-playback-state"
))

def get_now_playing():
    track = sp.current_user_playing_track()
    if track and track.get("is_playing"):
        item = track["item"]
        return {
            "title": item["name"][:20],
            "artist": item["artists"][0]["name"][:20],
            "progress_ms": track["progress_ms"],
            "duration_ms": item["duration_ms"]
        }
    return None

