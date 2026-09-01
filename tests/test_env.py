"""Basic sanity tests for the HeloEnv gymnasium environment.

These will fail until native/bindings.py is wired up to the real C model —
that's expected until the model arrives and is integrated. Kept here as a
starting scaffold / TODO marker.
"""
import gymnasium as gym
import pytest

import helo_env  # noqa: F401  (registers HeloEnv-v0)


def test_env_registered():
    assert "HeloEnv-v0" in gym.envs.registry


@pytest.mark.skip(reason="Requires compiled native model + wired-up bindings.py")
def test_reset_and_step():
    env = gym.make("HeloEnv-v0")
    obs, info = env.reset()
    assert env.observation_space.contains(obs)

    action = env.action_space.sample()
    obs, reward, terminated, truncated, info = env.step(action)
    assert env.observation_space.contains(obs)
    assert isinstance(reward, float)
