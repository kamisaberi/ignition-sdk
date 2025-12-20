# This is a test file for our Python SDK using the pytest framework.
# Its purpose is to ensure the core functionality works as expected.

import pytest
import numpy as np
import ignition as ig # This is the high-level Python package

# --- Mocks & Fixtures ---
# In a real test suite, you would create a dummy .plan file for testing.
# For this example, we will "mock" the internal C++ binding.

class MockEngine:
    """A mock of the C++ Engine for testing purposes."""
    def predict(self, inputs: dict) -> dict:
        # Simulate the behavior of the real engine
        input_array = list(inputs.values())[0]
        batch_size = input_array.shape[0]

        # Return a mock output with the correct batch size
        return {
            "output_layer_name": np.random.rand(batch_size, 1000).astype(np.float32)
        }

    @staticmethod
    def load(plan_path: str):
        if "good" in plan_path:
            return MockEngine()
        else:
            raise RuntimeError("Mock error: could not load plan.")

# `monkeypatch` is a pytest fixture for replacing functions during tests.
@pytest.fixture
def mock_internal_engine(monkeypatch):
    """This fixture replaces the real C++ Engine with our mock."""
    monkeypatch.setattr("ignition.infer.engine._internal.Engine", MockEngine)


# --- The Actual Tests ---

def test_engine_load_success(mock_internal_engine):
    """Tests that loading a valid engine file returns an Engine object."""
    model = ig.load("good_path.plan")
    assert model is not None
    assert isinstance(model, ig.Engine)

def test_engine_load_failure(mock_internal_engine):
    """Tests that loading an invalid file raises the correct exception."""
    with pytest.raises(RuntimeError, match="Mock error"):
        ig.load("bad_path.plan")

def test_engine_predict(mock_internal_engine):
    """Tests that the predict method returns an output with the correct shape."""
    model = ig.load("good_path.plan")

    # Create a dummy input with a batch size of 4
    dummy_input = np.random.rand(4, 3, 224, 224).astype(np.float32)

    results = model.predict({"input": dummy_input})

    assert isinstance(results, dict)
    assert "output_layer_name" in results

    output_array = results["output_layer_name"]
    assert isinstance(output_array, np.ndarray)

    # Check that the output batch size matches the input batch size
    assert output_array.shape == (4, 1000)