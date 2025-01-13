FROM ghcr.io/ad-sdl/wei

# TODO: update labels, if neccessary
LABEL org.opencontainers.image.source=https://github.com/AD-SDL/arduino_module
LABEL org.opencontainers.image.description="A template python module that demonstrates basic WEI module functionality."
LABEL org.opencontainers.image.licenses=MIT

#########################################
# Module specific logic goes below here #
#########################################

RUN mkdir -p arduino_module

COPY ./src arduino_module/src
COPY ./README.md arduino_module/README.md
COPY ./pyproject.toml arduino_module/pyproject.toml

RUN --mount=type=cache,target=/root/.cache \
    pip install ./arduino_module

# TODO: Add any device-specific container configuration/setup here

CMD ["python", "arduino_module.py"]

#########################################
